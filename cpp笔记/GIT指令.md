# 配置与初始化

`git config --global user.name `"你的名字"：设置你的用户名，该名称会关联到你的提交记录。
`git config --global user.email` "你的邮箱"：设置你的用户邮箱。
`git init`：在当前目录初始化一个新的本地 Git 仓库。
`git clone` <仓库地址>：将远程仓库克隆（复制）到本地。

# 基础操作（日常开发最常用）

`git status`：查看当前工作区的状态，了解哪些文件被修改、暂存或未被跟踪。
`git add` <文件名>：将指定文件添加到暂存区。如果想添加所有修改，可以使用 git add .。
`git commit -m` "提交说明"：将暂存区的文件提交到本地仓库，并附上提交说明。
`git diff`：查看工作区与暂存区之间文件的具体修改内容。
`git log`：查看提交历史记录。

# 分支管理

`git branch`：列出所有本地分支。
`git branch <分支名>`：创建一个新分支。
`git checkout <分支名>`：切换到指定分支。
`git checkout -b <分支名>`：创建并立即切换到新分支。
`git merge <分支名>`：将指定分支的更改合并到当前分支。
`git branch -d <分支名>`：删除指定的本地分支。

# 远程仓库操作

`git remote add origin <远程仓库地址>`：将本地仓库与远程仓库关联。
`git remote -v`：查看当前关联的远程仓库地址信息。
`git push origin <分支名>`：将本地分支的提交推送到远程仓库。
`git pull`：从远程仓库拉取最新的代码更新，并自动合并到本地当前分支16。

# 撤销与暂存

`git stash`：临时保存当前工作区未提交的修改，方便你切换到其他分支处理紧急事务。
`git stash pop`：恢复最近一次暂存的修改。
`git reset <文件名>`：将文件从暂存区移出，但保留工作区的修改（取消 git add）。
`git checkout -- <文件名>`：撤销工作区中指定文件的修改，恢复到上次提交的状态。