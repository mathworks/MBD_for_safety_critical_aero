function installHLRSolution(projectRoot)
%INSTALLHLRSOLUTION Unpack the ModeLogic HLR workshop solution files.
%
%   INSTALLHLRSOLUTION unpacks ModeLogic_HLR_Solution.zip into the root of
%   this workshop project.
%
%   INSTALLHLRSOLUTION(projectRoot) unpacks the solution into the specified
%   workshop project root.

arguments
    projectRoot (1,1) string = ""
end

solutionFolder = fileparts(mfilename("fullpath"));
archivePath = fullfile(solutionFolder, "ModeLogic_HLR_Solution.zip");

if projectRoot == ""
    projectRoot = fileparts(fileparts(solutionFolder));
end

if ~isfile(archivePath)
    error("AeroVnV:MissingHLRSolutionArchive", ...
        "Cannot find the HLR solution archive: %s", archivePath);
end

if ~isfolder(projectRoot)
    error("AeroVnV:MissingProjectRoot", ...
        "Cannot find the workshop project root: %s", projectRoot);
end

unzip(archivePath, projectRoot);
fprintf("Installed HLR solution files in: %s\n", projectRoot);
end
