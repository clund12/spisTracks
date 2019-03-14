% March 2nd 2016
% This function reads in all .csv files in a folder and creates a
% corresponding .mat file in a results directory. It also deletes the .csv
% files
% ex:
% spisTracks_Bin2Mat('/Users/Piotr/Documents/Geant4Work/builds/SPIS_final/spisTracks_valBF_10keV');
function CSVToMat(folderName)

    files = dir([folderName '/*.csv']);
    nFiles = length(files);
    
    for j = 1:nFiles

        display(['Converting track ' num2str(j) ' of ' num2str(nFiles)])
        fileName = [folderName '/' files(j).name];
        
        
        interactions = csvread(fileName, 18, 0);
        f2=[fileName(1:end-3) 'mat'];
        save(f2,'interactions','-mat','-v7.3');
        delete(fileName);


        % event ID; particle ID; process ID; pre-step point xyz; post-step point xyz;
        % pre-step kinetic energy; energy deposited; kinetic energy transferred;
        % track ID; parent ID;
%         recordType = {'integer*2' 'integer*2' 'integer*2' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'real*4' 'integer*2' 'integer*2'};
%         recordLen = [2 2 2 4 4 4 4 4 4 4 4 4 2 2];%#bytes for each field.
%         
%         fid1 = fopen(fileName);
%         data = cell(1,numel(recordType));
%         for i=1:numel(recordType)
%             fseek(fid1, sum(recordLen(1:i-1)), 'bof');
%             data{i}=fread(fid1,Inf,[recordType{i}], sum(recordLen)-recordLen(i));
%         end
%         fclose(fid1);
%         interactions = cell2mat(data);
%         f2=[fileName(1:end-3) 'mat'];
%         save(f2,'interactions','-mat','-v7.3');
%         delete(fileName);
    end
        
end
