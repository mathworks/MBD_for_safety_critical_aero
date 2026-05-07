classdef DOWorkshopTests < matlab.unittest.TestCase
%DOWorkshopTests Regression tests for the DO-178C/DO-331 Workshop
%
%   These tests validate that the workshop functions correctly after
%   updates or when run on a newer MATLAB release. Tests cover:
%   - Required toolbox availability
%   - Project and file integrity
%   - Model loading and Model Advisor runs
%   - Requirements loading
%   - Test suite execution
%
%   Usage:
%       results = runtests('DOWorkshopTests');
%       disp(results);
%
%   See also: matlab.unittest.TestCase, runtests

    properties (Constant)
        % Project root directory (relative to test file location)
        ProjectRoot = fileparts(fileparts(mfilename('fullpath')))
    end

    properties (TestParameter)
        % Required toolboxes for the workshop
        RequiredToolbox = { ...
            'Simulink', ...
            'Stateflow', ...
            'Simulink Check', ...
            'Simulink Test', ...
            'Simulink Coverage', ...
            'Simulink Design Verifier', ...
            'Requirements Toolbox'}

        % Test harness files that must exist and load
        TestHarnessFile = { ...
            'HLR_02a.slx', ...
            'HLR_02b.slx', ...
            'HLR_04.slx', ...
            'HLR_05.slx', ...
            'HLR_06.slx', ...
            'HLR_07.slx', ...
            'HLR_08.slx', ...
            'HLR_09a.slx', ...
            'HLR_09b.slx', ...
            'HLR_09c.slx', ...
            'HLR_09d.slx', ...
            'HLR_09e.slx', ...
            'HLR_10a.slx', ...
            'HLR_10b.slx', ...
            'HLR_10c.slx', ...
            'HLR_10d.slx', ...
            'HLR_10e.slx', ...
            'HLR_10f.slx', ...
            'HLR_10g.slx', ...
            'HLR_10h.slx', ...
            'HLR_10i.slx'}
    end

    properties (Access = private)
    end

    methods (TestClassSetup)
    end

    methods (TestMethodTeardown)
        function closeModels(testCase) %#ok<MANU>
            %closeModels Close all open models after each test
            bdclose('all');
            slreq.clear;
            sltest.testmanager.clear;
            sltest.testmanager.clearResults;
            sltest.testmanager.close;
        end
    end

    %% Environment and Setup Tests
    methods (Test, TestTags = {'Environment'})
        function testToolboxInstalled(testCase, RequiredToolbox)
            %testToolboxInstalled Verify required toolboxes are installed

            v = ver;
            installedProducts = {v.Name};
            testCase.verifyTrue( ...
                ismember(RequiredToolbox, installedProducts), ...
                sprintf('Required toolbox not installed: %s', RequiredToolbox));
        end

        function testMATLABVersionCompatibility(testCase)
            %testMATLABVersionCompatibility Verify MATLAB version is R2025b or newer
            testCase.verifyFalse( ...
                isMATLABReleaseOlderThan('R2025b'), ...
                'Workshop requires MATLAB R2025b or newer');
        end
    end

    %% File Integrity Tests
    methods (Test, TestTags = {'FileIntegrity'})
        function testInstructionsFileExists(testCase)
            %testInstructionsFileExists Verify main instructions file exists

            instructionsFile = fullfile(testCase.ProjectRoot, 'Instructions.mlx');
            testCase.verifyTrue(isfile(instructionsFile), ...
                'Instructions.mlx not found');
        end

        function testModeLogicModelExists(testCase)
            %testModeLogicModelExists Verify main design model exists

            modelFile = fullfile(testCase.ProjectRoot, ...
                'DO_03_Design', 'ModeLogic', 'specification', 'ModeLogic.slx');
            testCase.verifyTrue(isfile(modelFile), ...
                'ModeLogic.slx design model not found');
        end

        function testRequirementsFileExists(testCase)
            %testRequirementsFileExists Verify requirements file exists

            reqFile = fullfile(testCase.ProjectRoot, ...
                'DO_02_Requirements', 'specification', 'HLR_ModeLogic.slreqx');
            testCase.verifyTrue(isfile(reqFile), ...
                'HLR_ModeLogic.slreqx requirements file not found');
        end

        function testTestSuiteFileExists(testCase)
            %testTestSuiteFileExists Verify test suite file exists

            testFile = fullfile(testCase.ProjectRoot, ...
                'DO_03_Design', 'ModeLogic', 'test_cases', 'HLR', ...
                'ModeLogic_HLR_Tests.mldatx');
            testCase.verifyTrue(isfile(testFile), ...
                'ModeLogic_HLR_Tests.mldatx test file not found');
        end

        function testModelAdvisorConfigExists(testCase)
            %testModelAdvisorConfigExists Verify Model Advisor config exists

            configFile = fullfile(testCase.ProjectRoot, ...
                'tools', 'modelchecks', 'modelAdvisorQualifiableChecks.json');
            testCase.verifyTrue(isfile(configFile), ...
                'modelAdvisorQualifiableChecks.json not found');
        end

        function testDirectoryStructure(testCase)
            %testDirectoryStructure Verify DO lifecycle folder structure

            expectedDirs = { ...
                'DO_01_Planning', ...
                'DO_02_Requirements', ...
                'DO_03_Design', ...
                'DO_04_Code', ...
                'DO_05_Artifacts', ...
                'DO_06_ToolQualification'};

            for i = 1:numel(expectedDirs)
                dirPath = fullfile(testCase.ProjectRoot, expectedDirs{i});
                testCase.verifyTrue(isfolder(dirPath), ...
                    sprintf('Expected directory not found: %s', expectedDirs{i}));
            end
        end

        function testTestHarnessExists(testCase, TestHarnessFile)
            %testTestHarnessExists Verify each test harness file exists

            harnessPath = fullfile(testCase.ProjectRoot, ...
                'DO_03_Design', 'ModeLogic', 'test_cases', 'HLR', ...
                TestHarnessFile);
            testCase.verifyTrue(isfile(harnessPath), ...
                sprintf('Test harness not found: %s', TestHarnessFile));
        end
    end

    %% Part 1: Model Advisor and DED Tests
    methods (Test, TestTags = {'Part1', 'ModelAdvisor'})
        function testModeLogicModelLoads(testCase)
            %testModeLogicModelLoads Verify ModeLogic model loads without errors

            testCase.verifyWarningFree(@() load_system('ModeLogic'), ...
                'ModeLogic model failed to load or generated warnings');

            % Verify model is loaded
            testCase.verifyTrue(bdIsLoaded('ModeLogic'), ...
                'ModeLogic model did not load successfully');
        end

        function testModelAdvisorRuns(testCase)
            %testModelAdvisorRuns Verify Model Advisor checks execute successfully

            load_system('ModeLogic');

            % Run Model Advisor with the qualifiable checks configuration
            configFile = 'modelAdvisorQualifiableChecks.json';

            % Execute Model Advisor
            results = ModelAdvisor.run('ModeLogic', 'Configuration', configFile);

            testCase.verifyNotEmpty(results, ...
                'Model Advisor returned no results');
            testCase.verifyClass(results, 'cell', ...
                'Model Advisor results should be a cell array');
        end
    end

    %% Part 2: Requirements and Test Harness Tests
    methods (Test, TestTags = {'Part2', 'Requirements'})
        function testRequirementsSetLoads(testCase)
            %testRequirementsSetLoads Verify requirements set loads successfully

            reqSet = slreq.open('HLR_ModeLogic');

            testCase.verifyNotEmpty(reqSet, ...
                'Failed to open HLR_ModeLogic requirements set');
            testCase.verifyClass(reqSet, 'slreq.ReqSet', ...
                'Loaded object is not a valid requirements set');
        end

        function testTestManagerOpens(testCase)
            %testTestManagerOpens Verify Test Manager can be opened

            testCase.verifyWarningFree(@() sltest.testmanager.view, ...
                'Test Manager failed to open');
        end

        function testTestFileLoads(testCase)
            %testTestFileLoads Verify test file loads in Test Manager

            tf = sltest.testmanager.load('ModeLogic_HLR_Tests.mldatx');

            testCase.verifyNotEmpty(tf, ...
                'Failed to load ModeLogic_HLR_Tests.mldatx');
        end
    end

    %% Part 3: Test Execution
    methods (Test, TestTags = {'Part3', 'TestExecution'})
        function testSingleHarnessSimulates(testCase)
            %testSingleHarnessSimulates Verify a test harness can simulate

            harnessPath = fullfile(testCase.ProjectRoot, ...
                'DO_03_Design', 'ModeLogic', 'test_cases', 'HLR', 'HLR_02a.slx');

            load_system(harnessPath);
            [~, harnessName, ~] = fileparts(harnessPath);

            % Simulate the harness
            simOut = sim(harnessName);

            testCase.verifyNotEmpty(simOut, ...
                'Test harness simulation returned empty results');
        end
    end
end