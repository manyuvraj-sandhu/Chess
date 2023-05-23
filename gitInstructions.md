## Git Commits
# Introduction
Git commits should be made after small, changes to a program that you know work as they should and will not introduce new bugs into the program. For example, after you complete a method for an object, you should make a commit.

# How to Make a Git Commit
1) Type `git add filename` to add `filename` to the staging area.
2) Type `git status` to see a list of current files in the staging area.
3) Once you are ready to make your commit, type `git commit -m <message>`. The `-m <message>` command allows you to add a commit message to your commit. You should always add a short, informative commit message to your commits, i.e. `Implement Bishop::move`.
4) After a larger objective is completed (i.e. a class is coded), you should push the changes to the remote repository. Do this by typing the command `git push <remote> <branch>`, which pushes the branch to the remote repository, along with all commits you have made. To push to our repo, `<remote>` is `origin`.

# More information
Look at Git Cheatsheet.pdf for more information