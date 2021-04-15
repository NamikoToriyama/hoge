function SWSetCookie(name, value, expire, path)
{
    let cookie = name + '=' + escape(value);
    if(expire)
    {
        cookie += '; expires=' + expire.toGMTString();
    }
    if(path)
    {
        cookie += '; path=' + path;
    }
    document.cookie = cookie;
}

function SWGetCookie(name)
{
    let cookie = document.cookie;
    if(cookie && cookie.length > 0)
    {
        let offset = cookie.indexOf(name + '='); // if null return -1
        let end;
        if(offset != -1)
        {
            offset += name.length + 1;
            end     = cookie.indexOf(';', offset); // if null return -1
            if(end == -1)
            {
                end  = cookie.length;
            }
            return unescape(cookie.substring(offset, end)); // return cookie value
        }
    }
}