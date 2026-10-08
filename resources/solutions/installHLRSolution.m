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

modelPath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "specification", "ModeLogic.slx");
modelName = "ModeLogic";
harnessName = "HLR_03";
harnessPath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "test_cases", "HLR", harnessName + ".slx");
testFilePath = fullfile(projectRoot, "DO_03_Design", "ModeLogic", ...
    "test_cases", "HLR", "ModeLogic_HLR_Tests.mldatx");

if bdIsLoaded(modelName) && strcmp(get_param(modelName, "Dirty"), "on")
    error("AeroVnV:UnsavedModelChanges", ...
        "Save or discard changes to %s before installing the HLR solution.", ...
        modelName);
end

closeLoadedTestFile(testFilePath);
unzip(archivePath, projectRoot);

if ~isfile(modelPath) || ~isfile(harnessPath) || ~isfile(testFilePath)
    error("AeroVnV:IncompleteHLRSolution", ...
        "The HLR solution archive did not install all expected files.");
end

load_system(modelPath);
harnesses = sltest.harness.find(modelName);
harnessExists = any(strcmp({harnesses.name}, harnessName));

if ~harnessExists
    sltest.harness.import(modelName, ...
        "ImportFileName", harnessPath, ...
        "ComponentName", "ModeLogic", ...
        "Name", harnessName);
    save_system(modelName);
end

fprintf("Installed HLR solution files in: %s\n", projectRoot);
sltest.testmanager.load(testFilePath);
sltest.testmanager.view;
end

function closeLoadedTestFile(testFilePath)
% Close this file before replacing it, without discarding unsaved changes.

testFiles = sltest.testmanager.getTestFiles;
matchingFiles = strcmpi(string({testFiles.FilePath}), testFilePath);

for testFile = testFiles(matchingFiles)
    if testFile.Dirty
        error("AeroVnV:UnsavedTestFileChanges", ...
            "Save or discard changes to %s before installing the HLR solution.", ...
            testFilePath);
    end
    close(testFile);
end
end
