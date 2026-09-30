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

modelPath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "specification", "ModeLogic.slx");
modelName = "ModeLogic";
harnessPath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "test_cases", "HLR", "HLR_03.slx");
testFilePath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "test_cases", "HLR", "ModeLogic_HLR_Tests.mldatx");

if ~isfile(modelPath) || ~isfile(harnessPath) || ~isfile(testFilePath)
    error("AeroVnV:IncompleteHLRSolution", ...
        "The HLR solution archive did not install all expected files.");
end

open_system(modelPath);

if isempty(sltest.harness.find(modelName, "Name", "HLR_03"))
    sltest.harness.import(modelName, ...
        "ImportFileName", harnessPath, ...
        "ComponentName", "ModeLogic", ...
        "Name", "HLR_03");
end

fprintf("Installed HLR solution files in: %s\n", projectRoot);
open(testFilePath);
end
