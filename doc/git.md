# git使用总结

**描述**：在github上新建了一个仓库，然后主要在win下写文档并推送。另外想要在Linux下面获取远程最新的版本，继续编写，也推送到github。这样就需要解决两地同时使用的问题；（之前一直想做但是没有完成的事情）

- win下本地新建仓库：
	- git initgit 
	- add somefilesgit commit -m "comments"
	- git remote add origin YOUR_RES_ADDREgit push -u origin master （以后的push操作不需要加 -u）
  
- Linux下面clone这个仓库，修改之后再提交
	- git clone HTTPS_ADDRESS
	- git add somefilesgit commit -m "comments"
	- git config --global user.email "YOUR-EMAIL"
	- git config --global user.name "YOUR-NAME"
	- 因为第一次使用这个Linux系统推送文件到远程仓库，因此需要上面两个命令配置我的信息。

- 解决每次push操作都需要输入用户名和密码修改为ssh方式提交代码
	- git remote rm origin  删除原来的https链接
	- git remote add origin SSH-KEY  添加SSH链接

- 第一次使用某个电脑向github推送文件的时候，如果使用的https方式，那么每次可能都需要输入用户名和密码。如果选用SSH方式，那么需要把这个电脑的SSH添加到github上面。
	- Linux下面具体在 ~./ssh文件夹中

- 以后每次在win下或者Linux下面准备修改本地文件，准备提交之前，首先拉取一下仓库的最新版本，然后再进行修改。
	- git fetch origin master  下载远程master分支最新版本到本地master分支
	- git log -p master..origin/master  比较本地master分支和远程master分支的差别
	- git merge origin/master  合并到本地上述三个命令可以用下面一个替代
	- git pull origin master

- 其他辅助命令
	- git log  查看git提交历史
	- git log --graph --all  树图的形式查看git提交历史
	- git status  查看当前git 状态

- 如果本地版本和github上面的版本没有保持同步的情况下，我们又在本地做了修改怎么办？

没有关系。在没有及时pull最新版本到本地之前，可以任意在本地进行文档的修改。
当你本地修改完成后，这时是不能push的，需要先fetch下来，然后查看对比本地与github仓库中的区别，然后在进行merge操作。这时，git会将github中的最新版同步到本地，并保持本地的修改不变，然后就可以进行push操作了。

- 本地删除了某个文件怎么办？
可以直接通过 ``git rm`` 删除文件。然后再push。这时本地和github中的文件都会被删除。如果此时通过另一个终端（比如我在win下面删除之后，再在Linux下面操作）进行pull操作后，另一个终端本地下的文件也会同步的被删除。

- 同时删除本地仓库和远程仓库的文件夹
   正常直接在本地删除文件夹，然后正常add、commit、push就可以。

- 删除远程仓库的文件夹，保留本地
```
git pull origin master
git rm -r --cached file-NAME // cached选项不会把本地文件夹删除
git commit ...
git push...
```
