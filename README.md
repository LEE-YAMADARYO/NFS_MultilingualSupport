# NFS Multilingual Support
## Note: This project was assisted by an LLM. I am aware that some may not like this, but I believe I have an obligation to let everyone know.<br><br>
Restores the languages EA cut from the western builds of Black Box NFS. The same `.asi` file can be used for multiple games.
## Currently compatible game titles<br>
- NFS Most Wanted 2005<br>
- NFS Carbon<br>
- NFS ProStreet<br><br>
Restored/Added support for language entries: Chinese (Traditional), Chinese (Simplified), Japanese, Korean, Thai, Russian.<br><br>
All restored languages coexist with every stock one. In MW and Carbon, the Russian worked by overwriting the Finnish slot; this plugin instead appends Russian on a fresh id (14 / 19) and teaches the engine's registry name table about it, so Russian and Finnish are both available.<br>

## Install
1. Install an ASI loader (e.g. Ultimate ASI Loader's `dinput8.dll`) and drop `NFS_MultilingualSupport.asi` into the game `Scripts` folder.<br>
2. Place the Asian language resources you intend to use into the game; the plugin does not provide any Asian language resources, you must supply them yourself.<br>
3. Modify the registry or use the latest Widescreen Fix to set the language.<br>

## Important Notes
If you are using a Western build but wish to play the game in an Asian language, you must replace the memory files in your Western build with those from an Asian build. These files are typically located in the `GLOBAL` folder and follow the naming convention `XNAME_MemoryFile.bin` for example, `GlobalMemoryFile.bin`, `InGameMemoryFile.bin`, and so on. Otherwise, the western packs lack the CJK data: Most Wanted crashes at boot, Carbon crashes entering race selection. (Note: This step is not required for ProStreet)<br>

## Recommended pairings
You can use this plugin alongside `KyoriAsh`'s Multi-language Selector mod.<br>
- MW: https://nfsmods.xyz/mod/5795<br>
- Carbon: https://nfsmods.xyz/mod/5802<br>
- ProStreet: https://nfsmods.xyz/mod/5826<br><br>
These mod includes all commonly used regional languages, as well as sound and texture assets, and MemoryFile.<br>

## Known issues
1. When using languages ​​supported by this plugin in ProStreet, the corresponding audio may fail to play if those languages ​​include their own dub audio, This is due to differences in the formats of the native audio resources for certain languages, the exact details are not yet fully clear.<br>
2. When using a language that includes its own dub audio in Carbon, you must ensure that the corresponding sound assets are present, otherwise, it may result in an infinite loading loop.<br><br>
There may well be more, but given the vast scope of the game, it is impossible for me to test every single edge case. If you encounter any issues, please submit an issue.<br>

## TODO
1. Attempt to identify the root cause of known issues and fix them.<br>
2. Add support for Undercover (it had better be that way).<br><br>

# NFS Multilingual Support_Chinese
## 注意：此项目使用 LLM 辅助，我知道会有人不喜欢 AI 生成的东西，但我认为我有义务让每个人知道这一点.<br><br>
此插件用于对 EA 在黑盒工作室 (Black Box) 的《极品飞车》系列游戏的西方版本中移除的语言重新添加支持. 插件同时支持多个游戏.<br>
## 兼容的游戏列表<br>
- 极品飞车：最高通缉 2005 (Most Wanted)<br>
- 极品飞车：卡本峡谷 (Carbon)<br>
- 极品飞车：街头狂飙 (ProStreet)<br><br>
恢复/新增了对以下语言的支持：繁体中文、简体中文、日语、韩语、泰语、俄语.<br><br>
所有恢复的语言均可与游戏原有的语言共存. 在 MW 和 Carbon 中，俄语原本是通过覆盖芬兰语槽位来实现的；而插件则使用新的 ID（14 或 19）添加俄语，并向游戏引擎的注册名称表中注册该语言，从而确保俄语和芬兰语同时可用.<br>

## 安装
1. 安装 ASI 加载器（例如 Ultimate ASI Loader 的 `dinput8.dll`），并将 `NFS_MultilingualSupport.asi` 放入游戏的 `Scripts` 文件夹中.<br>
2. 将需要使用的亚洲语言资源放入游戏中，该插件不提供任何亚洲语言资源，请自行准备.<br>
3. 修改注册表或使用最新的宽屏补丁 `Widescreen Fix` 来设置语言.<br>

## 注意事项
如果你当前正在使用西方版本的游戏本体，但需要使用亚洲语言，则必须获取亚洲版本的内存文件对西方版本的内存文件进行替换，它们通常为游戏目录 `GLOBAL\` 文件夹的 `名称_MemoryFile.bin` 文件，例如 `GlobalMemoryFile.bin` 或 `InGameMemoryFile.bin` 等. 否则，由于西方版本资源包缺少 CJK 数据，​​会导致 MW 在启动时崩溃，Carbon 在进入某些前端界面时崩溃等问题.（注意：ProStreet 不需要进行这一步操作）<br>

## 推荐搭配
你可以将此模组与 `KyoriAsh` 制作的多语言选择器模组（Multi-language Selector mod）搭配使用.<br>
- MW：https://nfsmods.xyz/mod/5795<br>
- Carbon：https://nfsmods.xyz/mod/5802<br>
- ProStreet: https://nfsmods.xyz/mod/5826<br><br>
这些模组包含所有常用地区语言的语言、音频、纹理等资源文件以及内存文件.<br>

## 已知问题
1. 在 ProStreet 中使用本插件提供支持的语言时，如果该语言包含专属配音，可能会出现部分 Speech/NIS 音频无法播放/缺失部分 Speech/NIS 声音的情况，这可能是由于部分语言的自有音频资源格式差异所致，具体细节尚不完全清楚.<br>
2. 在 Carbon 中使用包含专属配音的语言时，必须确保相应的音频资源已完整提供，否则可能会导致游戏陷入无限载入循环.<br><br>
可能仍然存在其他问题，但由于游戏数量多且体量较大，我无法测试到每一种极端和边界情况，如果遇到任何问题，请在此仓库提交 Issue.

## 待办事项
1. 尝试修复已知问题.
2. 添加对《极品飞车：卧底风云》(Undercover) 的支持（也许）
