# NFS Multilingual Support_English
Restores the languages EA cut from the western builds of NFS MW & NFS Carbon. One `.asi` serves both games; a byte-level fingerprint identifies the host and a mismatching executable is left untouched.<br><br>
Compatible with NFS MW 1.3 exe and NFS Carbon 1.4 exe.<br>
Restored/Added support for language entries: Chinese (Traditional), Chinese (Simplified), Japanese, Korean, Thai, Russian<br><br>
All restored languages coexist with every stock one, including Finnish. The official Russian releases worked by overwriting the Finnish slot; this plugin instead appends Russian on a fresh id (14 / 19) and teaches the engine's registry name table about it, so Russian and Finnish are both available.<br><br>

## Install
1.Install an ASI loader (e.g. Ultimate ASI Loader's `dinput8.dll`) and drop `NFS_MultilingualSupport.asi` into the game `Scripts` folder.<br>
2.Place the Asian language resources you intend to use into the game; the plugin does not provide any Asian language resources—you must supply them yourself.<br>
3.Modify the registry or use the latest Widescreen Fix to set the language.<br><br>

## Important Notes:
If you are on a western game build but want Asian languages, you must obtain the Asian release's memory files and replace the western ones in `GLOBAL\` - `GlobalMemoryFile.bin` and `InGameMemoryFile.bin` (`CarHeadersMemoryFile.bin` only exists on Carbon). Otherwise, the western packs lack the CJK data: Most Wanted crashes at boot, Carbon crashes entering race selection.<br><br>
PermanentMemoryFile.bin / FrontEndMemoryFile.bin / ShadersMemoryFile.bin It does not appear to be loaded by PC exe, so don't matter.<br><br>

## Recommended pairings:
You can use this plugin alongside `KyoriAsh`'s MW and Carbon Multi-language Selector mod.<br><br>
MW: https://nfsmods.xyz/mod/5795<br>
Carbon: https://nfsmods.xyz/mod/5802<br><br>
This mod includes all Asian language assets and memory files.<br><br>

## Known issues:
None found so far, if any exist, please submit an issue.<br><br>

## TODO
Add Asian language support for ProStreet.<br><br><br><br>

# NFS Multilingual Support_Chinese
此插件用于对 EA 在《极品飞车：最高通缉》（NFS MW）和《极品飞车：卡本峡谷》（NFS Carbon）西方版本中移除的亚洲语言重新添加支持. 插件同时支持这两款游戏：通过特征码识别宿主程序，若检测到不匹配的可执行文件则不进行任何操作.<br><br>
兼容《极品飞车：最高通缉》1.3 版本及《极品飞车：卡本峡谷》1.4 版本可执行文件.<br>
恢复/新增了对以下语言的支持：繁体中文、简体中文、日语、韩语、泰语、俄语.<br><br>
所有恢复的语言均可与游戏原有的语言共存. 其中，官方俄语版本原本是通过覆盖芬兰语槽位来实现的；而插件则使用新的 ID（14 或 19）添加俄语，并向游戏引擎的注册名称表中注册该语言，从而确保俄语和芬兰语同时可用.<br><br>

## 安装
1.安装 ASI 加载器（例如 Ultimate ASI Loader 的 `dinput8.dll`），并将 `NFS_MultilingualSupport.asi` 放入游戏的 `Scripts` 文件夹中.<br>
2.将您打算使用的亚洲语言资源放入游戏中，该插件不提供任何亚洲语言资源，您必须自行准备.<br>
3.修改注册表或使用最新的宽屏补丁 `Widescreen Fix` 来设置语言.<br><br>

## 注意事项：
如果您正在使用西方版本的游戏本体，但想要使用亚洲语言，则必须获取亚洲版本的内存文件，并替换 `GLOBAL\` 目录下的西方版本同名文件：`GlobalMemoryFile.bin` 和 `InGameMemoryFile.bin`（Carbon 则独有 `CarHeadersMemoryFile.bin`）否则，由于西方版本资源包缺少 CJK（中日韩）数据，​​会导致 MW 在启动时崩溃，而 Carbon 则会在进入比赛选择界面时崩溃.<br><br>
至于 `PermanentMemoryFile.bin`、`FrontEndMemoryFile.bin` 和 `ShadersMemoryFile.bin`，PC 版本似乎不会加载它们，因此无需替换.<br><br>

## 推荐搭配：
你可以将此模组与 `KyoriAsh` 制作的 MW 和 Carbon 多语言选择器模组（Multi-language Selector mod）搭配使用.<br><br>
MW：https://nfsmods.xyz/mod/5795<br>
Carbon：https://nfsmods.xyz/mod/5802<br><br>
本模组已包含所有亚洲语言的资源文件及内存文件.<br><br>

## 已知问题：
目前尚未发现任何问题；如有发现，请提交问题报告.<br><br>

## 待办事项
为 ProStreet 添加亚洲语言支持.<br><br>