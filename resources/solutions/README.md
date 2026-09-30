# ModeLogic HLR solution archive

`ModeLogic_HLR_Solution.zip` contains the HLR test-case solution set only.
Its contents retain their project-relative paths, so unpack it at the root of
the main workshop repository.

In MATLAB, from the main workshop root:

```matlab
installHLRSolution
```

The installer is in the same folder as the archive. Run it by opening
`resources/solutions/installHLRSolution.m` and clicking **Run**, or use:

```matlab
addpath(fullfile("resources", "solutions"))
installHLRSolution
```

The archive adds:

```text
DO_03_Design/ModeLogic/test_cases/HLR/
```

It intentionally does not duplicate the starter workshop's `ModeLogic.slx`,
`ModeLogic_data.sldd`, or requirements files. Those files must already be
present in the compatible main workshop.

To rebuild the archive from this solution repository, run:

```matlab
createHLRSolutionZip
```

from the `tools` folder, or add that folder to the MATLAB path first.
