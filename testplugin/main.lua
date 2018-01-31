local plugin_info = 
{
    api_ver = 1,
    identifier = "miigon.testplugin",
}

function initialize()
    print "[xPatche] Testplugin initialize."
    xp.listen("main_window.load",function()
        
    end)
    

    return true
end

return plugin_info