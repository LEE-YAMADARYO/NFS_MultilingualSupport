# NFS Multilingual Support_English
Restores the languages EA cut from the western builds of Black Box NFS. The same `.asi` file can be used for multiple games; a byte-level fingerprint identifies the host and a mismatching executable is left untouched.<br><br>
## Currently compatible game titles:<br>
- NFS Most Wanted 2005<br>
- NFS Carbon<br>
- NFS ProStreet<br><br>
Restored/Added support for language entries: Chinese (Traditional), Chinese (Simplified), Japanese, Korean, Thai, Russian<br><br>
All restored languages coexist with every stock one. In MW and Carbon, the official Russian releases worked by overwriting the Finnish slot; this plugin instead appends Russian on a fresh id (14 / 19) and teaches the engine's registry name table about it, so Russian and Finnish are both available.<br><br>

## Install
1. Install an ASI loader (e.g. Ultimate ASI Loader's `dinput8.dll`) and drop `NFS_MultilingualSupport.asi` into the game `Scripts` folder.<br>
2. Place the Asian language resources you intend to use into the game; the plugin does not provide any Asian language resources—you must supply them yourself.<br>
3. Modify the registry or use the latest Widescreen Fix to set the language.<br><br>

## Important Notes:
If you are on a western game build but want Asian languages, you must obtain the Asian release's memory files and replace the western ones in `GLOBAL\` - `XNAME_MemoryFile.bin`, For example `GlobalMemoryFile.bin` or `InGameMemoryFile.bin`, etc. Otherwise, the western packs lack the CJK data: Most Wanted crashes at boot, Carbon crashes entering race selection. (No clear issues have emerged with ProStreet yet.)<br><br>

## Recommended pairings:
You can use this plugin alongside `KyoriAsh`'s Multi-language Selector mod.<br>
- MW: https://nfsmods.xyz/mod/5795<br>
- Carbon: https://nfsmods.xyz/mod/5802<br>
- ProStreet: https://nfsmods.xyz/mod/5826<br><br>
These mod includes all Asian language assets and memory files.<br><br>

## Known issues:
1. Using Japanese in Carbon may cause the game to get stuck in an infinite loading loop when loading a race.<br>
2. ProStreet may experience random crashes, and Japanese NIS audio might not work.<br>

## TODO
Attempt to identify the root cause of known issues and fix them.<br><br><br><br>

# NFS Multilingual Support_Chinese
此插件用于对 EA 在黑盒工作室的《极品飞车》系列游戏的西方版本中移除的亚洲语言重新添加支持. 插件同时支持多个游戏：通过特征码识别宿主程序，若检测到不匹配的可执行文件则不进行任何操作.<br><br>
## 兼容的游戏列表:<br>
- 极品飞车：最高通缉 2005 (Most Wanted)<br>
- 极品飞车：卡本峡谷 (Carbon)<br>
- 极品飞车：街头狂飙 (ProStreet)<br><br>
恢复/新增了对以下语言的支持：繁体中文、简体中文、日语、韩语、泰语、俄语.<br><br>
所有恢复的语言均可与游戏原有的语言共存. 在 MW 和 Carbon 中，官方俄语版本原本是通过覆盖芬兰语槽位来实现的；而插件则使用新的 ID（14 或 19）添加俄语，并向游戏引擎的注册名称表中注册该语言，从而确保俄语和芬兰语同时可用.<br><br>

## 安装
1. 安装 ASI 加载器（例如 Ultimate ASI Loader 的 `dinput8.dll`），并将 `NFS_MultilingualSupport.asi` 放入游戏的 `Scripts` 文件夹中.<br>
2. 将您打算使用的亚洲语言资源放入游戏中，该插件不提供任何亚洲语言资源，您必须自行准备.<br>
3. 修改注册表或使用最新的宽屏补丁 `Widescreen Fix` 来设置语言.<br><br>

## 注意事项：
如果您正在使用西方版本的游戏本体，但想要使用亚洲语言，则必须获取亚洲版本的内存文件，也就是游戏目录 `GLOBAL\` 文件夹的 `名称_MemoryFile.bin` 文件，例如 `GlobalMemoryFile.bin` 或 `InGameMemoryFile.bin` 等. 否则，由于西方版本资源包缺少 CJK（中日韩）数据，​​会导致 MW 在启动时崩溃，而 Carbon 则会在进入比赛选择界面时崩溃.（ProStreet 暂未发现明显存在的问题）<br><br>

## 推荐搭配：
你可以将此模组与 `KyoriAsh` 制作的多语言选择器模组（Multi-language Selector mod）搭配使用.<br>
- MW：https://nfsmods.xyz/mod/5795<br>
- Carbon：https://nfsmods.xyz/mod/5802<br>
- ProStreet: https://nfsmods.xyz/mod/5826<br><br>
这些模组已包含所有亚洲语言的资源文件及内存文件.<br><br>

## 已知问题：
1. 在 Carbon 中使用日语可能会导致游戏在加载比赛时陷入无限加载循环.<br>
2. ProStreet 可能会出现随机崩溃，且日语 NIS 音频可能无法正常工作.<br><br>

## 待办事项
尝试修复已知问题.<br><br>