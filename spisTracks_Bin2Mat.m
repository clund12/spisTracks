% March 2nd 2016
% This function reads in all .bin files in a folder and create a
% corresponding .mat file in a results directory. It also deletes the .bin
% files
% ex:
% spisTracks_Bin2Mat('/Users/Piotr/Documents/Geant4Work/builds/SPIS_final/spisTracks_valBF_10keV');
function spisTracks_Bin2Mat(folderName)

    files = dir([folderName '/*.bin']);
    nFiles = length(files);
    
    for j = 1:nFiles
        fileName = [folderName '/' files(j).name];

        % interactionID (1 if first interaction in volume, 0 if not)...
        % flagProcess (30 = phot, 31 = compt, 32 = conv, 33 =
        % Rayl, 0 = other)
        % volID (1 = SV, 2 = small vol, 3 = normal vol, 4 = large vol)
        % Pos X,Y,Z with center in the middle of the phantom.
        % Kin Energy pre interaction (eV)
        % momentum direction XYZ, normalized to 1.
        recordType = {'real*4' 'integer*2' 'integer*2' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'integer*2' 'integer*2'};
        recordLen = [4 2 2 4 4 4 4 4 4 4 4 4 2 2];%#bytes for each field.
        
        fid1 = fopen(fileName);
        data = cell(1,numel(recordType));
        for i=1:numel(recordType)
            fseek(fid1, sum(recordLen(1:i-1)), 'bof');
            data{i}=fread(fid1,Inf,[recordType{i}], sum(recordLen)-recordLen(i));
        end
        fclose(fid1);
        interactions = cell2mat(data);
        f2=[fileName(1:end-3) 'mat'];
        save(f2,'interactions','-mat','-v7.3');
        delete(fileName);
    end
        
end

% 
% function interactions = Bin2Mat2(fileName)
% 
%          tic;
%         % interactionID (1 if first interaction in volume, 0 if not)...
%         % flagProcess (30 = phot, 31 = compt, 32 = conv, 33 =
%         % Rayl, 0 = other)
%         % volID (1 = SV, 2 = small vol, 3 = normal vol, 4 = large vol)
%         % Pos X,Y,Z with center in the middle of the phantom.
%         % Kin Energy pre interaction (eV)
%         % momentum direction XYZ, normalized to 1.
%         recordType = {'integer*2' 'integer*2' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'integer*2' 'integer*2'};
%         recordLen = [2 2 4 4 4 4 4 4 2 2];%#bytes for each field.
%         
%         fid1 = fopen(fileName);
%         data = cell(1,numel(recordType));
%         for i=1:numel(recordType)
%             fseek(fid1, sum(recordLen(1:i-1)), 'bof');
%             data{i}=fread(fid1,Inf,[recordType{i}], sum(recordLen)-recordLen(i));
%         end
%         fclose(fid1);
%         interactions = cell2mat(data);
% %         f2=[fileName(1:end-3) 'mat'];
% %         save(f2,'interactions','-mat','-v7.3');
%         toc;
% end