local plugin_info = 
{
    api_ver = 1,
    identifier = "miigon.testplugin",
}
local welcome_msg = [[
欢迎使用 xPatche!
IINA 脚本引擎 - xPatche
为 IINA 提供更强大的 Lua 脚本执行能力。

]]

function initialize()
    print "[xPatche] Testplugin initialize."
    xp.listen("initial_window.load",function()
        xp.listen_stop"initial_window.load"
        print "load"
    end)

    xp.listen("open_media",function()
        xp.alert "这是你本次运行IINA后播放的第一个视频！"
        xp.listen_stop"open_media"
        xp.open_media(xp.get_current_url())
        --xp.alert("你已经安装了 IINA-Blocker 插件\n本插件将会阻止你打开任何视频！\n祝你生活愉快~")
        --xp.alert(xp.get_current_url())
        return true
    end)
    

    return true
end

return plugin_info