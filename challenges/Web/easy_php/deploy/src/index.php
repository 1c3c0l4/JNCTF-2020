
<?php

header("content-type:text/html;charset=utf-8");
include('flag.php');

function isture($web){
    return preg_match('/hello.*jnuer/is',$web);
}
$web=@$_POST['web'];
   if(!isture($web)){
        if(strpos($web,'hello jnuer')!==false){
           echo $flag;
 
        }else{
			
			echo '你想学习正则匹配吗？';
            echo 'https://deerchao.cn/tutorials/regex/regex.htm';
        }
    }else{
        echo 'Do you know PHP?';
    }
?>
<?php show_source(__FILE__);?>