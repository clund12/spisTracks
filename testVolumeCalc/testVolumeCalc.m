%function [aAV] = testVolumeCalc(D, R)
D = [1 2 3; 4 5 6; 1 2 3; 3 2 1];
%D = [1 2 3; 4 5 6];
%D = [1 2 3];

R = 2;

voxel_side = 2*R;
A = [voxel_side/2 voxel_side/2 voxel_side/2];
d = D + A(ones(size(D,1),1),:);

voxel_pos = unique(floor(bsxfun(@rdivide,d(:,1:3),voxel_side)),'rows');

n_voxels = size(voxel_pos,1);
add_vox = cell(n_voxels,1);
n_pad = 1;

for j = 1:n_voxels
    X = voxel_pos(j,1);
    Y = voxel_pos(j,2);
    Z = voxel_pos(j,3);
    [X1,Y1,Z1] = meshgrid(X-n_pad:X+n_pad,Y-n_pad:Y+n_pad,Z-n_pad:Z+n_pad);
    add_vox{j} = [X1(:),Y1(:),Z1(:)];    
end

cellvox = cell2mat(add_vox);
uniquevox = unique(cellvox, 'rows');
voxCentres = bsxfun(@times, voxel_pos, voxel_side) + voxel_side/2;
n_unique = size(uniquevox,1);
aAV = n_unique * voxel_side^3;
%aAV = 1
