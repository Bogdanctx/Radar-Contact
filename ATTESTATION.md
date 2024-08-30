# Check if a release archive matches with its own commit

---

###  To ensure that a downloaded archive from a release matches its own commit and hasn't been tampered, follow the steps below

### => Step 1: Download and install [GitHub CLI](https://cli.github.com/)
### => Step 2: Open a terminal and type ``gh auth login`` and follow the instructions (skip this step if GitHub CLI has been already configured)
### => Step 3: Open a terminal and type `gh attestation verify path_to_zip_file -R Bogdanctx/Radar-Contact`

#### Example: ``C:\Users\username\Downloads> gh attestation verify Radar-Contact_windows.zip -R Bogdanctx/Radar-Contact`` (Radar-Contact_windows.zip was located in Downloads directory)

### After the verification is complete you should see in terminal <span style="color: green">Verification succeded!</span>. This means the downloaded archive matches the release commit and has not been tampered.