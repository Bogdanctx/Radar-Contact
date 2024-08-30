# Checking if Radar Contact binaries were tampered

---

### Verifying the binaries of a release ensures that what you download matches the commit from which the release was created.

### What does this means? 
#### It means that archieves ``Radar-Contact_ubuntu-22.04.zip`` or ``Radar-Contact_windows.zip`` have the same source code as in the commit marked with the red rectangle. (In this case, ``v3.6`` binaries source code will match with commit ``c1c4526``. To check ``c1c4526`` source code click on it and then press ``Browse files`` in the right side of the screen).
![](./attestation/commit.png)

### To do this follow the steps below.

### => Step 1: Download and install [GitHub CLI](https://cli.github.com/)
### => Step 2: Open a terminal and type ``gh auth login`` and follow the instructions (skip this step if GitHub CLI has been already configured)
### => Step 3: Open a terminal and type `gh attestation verify path_to_zip_file -R Bogdanctx/Radar-Contact`

#### Example: ``C:\Users\username\Downloads> gh attestation verify Radar-Contact_windows.zip -R Bogdanctx/Radar-Contact`` (``Radar-Contact_windows.zip`` was located in ``Downloads`` directory)

### After the verification is complete you should see in terminal <code style="color: green">Verification succeded!</code>. This means that the binaries haven't been tampered and their source code matches the release commit's source code (i.e. the commit marked with a red rectangle in the image above).