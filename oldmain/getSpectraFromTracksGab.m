

% March 9 2016

% TEST SCRIPT TO COMPARE CURRENT METHOD (RANDOM POSITION IN VOXELS) TO
% RANDOM POSITION AROUND ENERGY TRANSFER, TO FIRST METHOD (CROSSING)
% Function that reads all tracks in folderName and outputs an fe, fp and zf for a given
% RSV value. N refers to the number of times each track is sampled,
% max_nTracks to the maximal number of tracks to sample
% example
% [fe, fp, zf] = getSpectraFromTracks('/Users/Piotr/Documents/Geant4Work/builds/SPIS_final/spisTracks_valBF_10keV',RSV, n, max_nTracks)
function [Z2, W2, AV, aAV, y_F, y_D] = getSpectraFromTracksGab(folderName, RSV, n, max_nTracks)
    % RSV = scoring volums radius, n = number of samples taken per track
    files = dir([folderName '/track*.mat']);
    nFiles = min([length(files),max_nTracks]); % limit to max_nTracks tracks
    
    % Initialize
%     Z = cell(nFiles,1); W = Z; eS = Z; pS = Z; aAV = Z; AV = Z;eEK=Z;eEDEP=Z;
        Z2 = cell(nFiles,1); % energy deposits
        W2 = Z2; % weight associated to each sample
        aAV = Z2; % approximate track weight (volume of all voxels)
        AV = Z2; % correction to weight (npointsIN / npointsTOTAL)
        eS = Z2; % unused
        pS = Z2; % ' '

    for i = 1:nFiles
        display(['Starting track ' num2str(i) ' of ' num2str(nFiles)])
        load([folderName '/' files(i).name]); % load interactions
        track = interactions(:,[4:6 11 7:9 10 2 13 14]); % 4:6 post-step, 7-9 pre-step, etc. (refer to EventAction.cc)
        clear interactions;
        [AV{i}, aAV{i}] = getTrackAssociateVolumeGAB(track, RSV, 10*n); 
        [Z2{i}, W2{i}, eS{i}, pS{i}] = sampleTrackAssociatedVolumeGAB(track, n, RSV);
    end

    %%% DO SOMETHING WITH THESE.
    temp = gmultiply(Z2,W2);
    temp = sum([temp{:}],1);
    y_F = temp./sum([W2{:}],1)*cell2mat(aAV)/sum(cell2mat(aAV))./(4/3*RSV); % Denominator of Eq. 3 from Famulari et al. (2017)
    temp2 = gmultiply(gmultiply(Z2,Z2),W2);
    temp2 = sum([temp2{:}],1);
    y_F2 = temp2./sum([W2{:}],1)*cell2mat(aAV)/sum(cell2mat(aAV))./(4/3*RSV)^2;
    %y_F = (cell2mat(Z2)./(4/3*RSV))'*((cell2mat(gmultiply(W2,aAV)))/sum(cell2mat(gmultiply(W2,aAV))));
    %y_F2 = (cell2mat(Z2)./(4/3*RSV))'.^2*((cell2mat(gmultiply(W2,aAV)))/sum(cell2mat(gmultiply(W2,aAV))));
    y_D = y_F2/y_F;
    %sigma_y_F = sqrt(y_F*y_D/(n*max_nTracks));
    %sigma_y_F = sqrt(y_F2-y_F.^2)/sqrt(n*max_nTracks);
    %sigma_y_D = y_D*sqrt((2*y_F*sigma_y_F/y_F2).^2+(sigma_y_F/y_F).^2);
    
    
end
function [Z,W,eS,pS] = sampleTrackAssociatedVolumeGAB(track,n,R)
% function [Z,W] = sampleTrackAssociatedVolumeGAB(track,n,R)
    R2 = R^2;
    isRelevantTP = track(:,4) > 0; % finds relevant transfer points (eDep > threshold)
    allRelevantTPs = track(isRelevantTP,:); % filters out irrelevant transfer points
     %[~,~,ROOT] = kdtree(track(:,1:3),[]); % Generate KDTree.
    nTP = randi(sum(isRelevantTP),n,1); % # nx1 array of random integers in [1, # of relevant TPs]
    Points = getPointsInBallGAB(R,n); % random distances <= sampling radius
    testPoints = allRelevantTPs(nTP,1:3) + Points; % random sampling positions near relevant TPs
    Z = zeros(n,1); W = Z; 
    eS = cell(n,1); pS = eS;
    for i = 1:n
        tp = testPoints(i,:);
        % Find transfer points within the sampling sphere
        IDXneighbours = sum((bsxfun(@minus,track(:,1:3),tp).^2),2)<R2;
        % Get the energy deposited by these test points and sum them
        eds = track(IDXneighbours,4);
        % Chord length will be divided out later
        Z(i) = sum(eds);
        % Calculate weight (1/number of energy deposits, as long as there is at least 1)
        W(i) = 1/numel(eds(eds>0));
        % Get the rest of the data for the neighbouring points
        %Prev = track(IDXneighboors,:);
        % Check if pre-step is not in the sampling volume
        %isNotIn = sum(bsxfun(@minus, Prev(:,5:7),tp).^2,2)>R2; 
        % Check if this point was due to an electron interaction (and is not in the sampling volume)
        % If so, add its pre-step kinetic energy to eS
        %validEl = Prev(:,9)==1 & isNotIn;
        %eS{i} = Prev(validEl,8);            
        %pS{i} = Prev(Prev(:,9)==7 & Prev(:,4)>0,8);  
    end
     %kdtree([],[],ROOT);
end
function p = getPointsInBallGAB(R, n)
    r = R.*(rand(n,1)).^(1/3); % probability should scale with volume
    theta = asin(2*rand(n,1)-1); % -pi/2 to pi/2
    phi = 2*pi*rand(n,1);
    [x,y,z] = sph2cart(phi,theta,r);
    p = [x y z];
end
function [AV, aAV] = getTrackAssociateVolumeGAB(track, R, n) 
    D = track(track(:,4)>0,1:3); % post-step positions of relevant transfer points
    voxel_side = 2*R; % cube inscribed by sampling sphere
    A = [voxel_side/2 voxel_side/2 voxel_side/2];
    d = D + A(ones(size(D,1),1),:); % offset every point of D by A
        voxel_pos = unique( % keep only unique rows
            floor( % floor the division
            bsxfun(@rdivide, d(:,1:3), voxel_side) % divide every point of d by voxel_side
            ),
            'rows'); % In full, assign each point a unique, integer-based position - voxelize the track
        n_voxels = size(voxel_pos,1);
        add_vox = cell(n_voxels,1); % n x 1 cell array
        n_pad = ceil(2*R./voxel_side); % but why? this is just 1
        for j = 1:n_voxels % for each voxel 
             X = voxel_pos(j,1); 
             Y = voxel_pos(j,2);
             Z = voxel_pos(j,3);
             [X1,Y1,Z1] = ...
                 % each voxel is expanded out by one position in each direction
                 meshgrid(X-n_pad:X+n_pad,Y-n_pad:Y+n_pad,Z-n_pad:Z+n_pad);
             add_vox{j} = [X1(:),Y1(:),Z1(:)];
        end
        voxel_pos = unique(cell2mat(add_vox),'rows'); % add Neighboors
        voxCenters = bsxfun(@times, voxel_pos, voxel_side) + voxel_side/2; % expand unit voxels to proper size; set the centre
        n_voxels = size(voxel_pos,1); % number of connected voxels (the 'track')
        aAV = n_voxels * voxel_side.^3; % volume of the connected cubes
        AV = aAV;
        % This bit is longer and calculated the volume numerically using
        % kdtrees.
         %voxID = randi(n_voxels,n,1);
         %pts = voxCenters(voxID,:) + voxel_side.*(rand(n,3) - 0.5);
         %[~, Distances, ROOT] = kdtree(D, pts);
         %AV = sum(Distances<=R)/n;
         %kdtree([],[],ROOT);
end 
