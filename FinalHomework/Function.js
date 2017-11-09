//判断填写是否为空，判断填写是否是邮箱地址
function JudgeLegal()
{
    var x=document.forms["Must"]["MustA"].value;
    if (x===null || x===""){
        alert("姓名必须填写");
        return false;
    }
    x = document.forms["Must"]["MustB"].value;
    if (x===null || x==="") {
        alert("邮箱必须填写");
        return fale;
    }
    x = document.forms["Must"]["MustC"].value;
    if (x===null || x==="") {
        alert("密码必须填写");
        return fale;
    }
    x = document.forms["Must"]["MustD"].value;
    if (x===null || x==="") {
        alert("学院必须填写");
        return fale;
    }
    x=document.forms["Must"]["MustB"].value;
    var atpos=x.indexOf("@");
    var dotpos=x.lastIndexOf(".");
    if (atpos<1 || dotpos<atpos+2 || dotpos+2>=x.length) {
        alert("请填写有效的e-mail地址！");
        return false;
    }
}

function showps()
{
    if (this.forms.MustC.type="password") {
        document.getElementById("box").innerHTML="<input type=\"text\" name=\"MustC\" value="+this.forms.password.value+">";
        document.getElementById("click").innerHTML="<a href=\"javascript:hideps()\">隐藏密码</a>"
    }
}
function hideps(){
    if (this.forms.MustC.type="text") {
        document.getElementById("box").innerHTML="<input type=\"password\" name=\"MustC\" value="+this.forms.password.value+">";
        document.getElementById("click").innerHTML="<a href=\"javascript:showps()\">显示密码</a>"
    }
}


