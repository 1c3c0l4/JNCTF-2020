<?php
header('Content-Type:text/html;charset=utf-8');
$var="ac2oyOJqcMTL3W2p";
include  "flag.php";
function encode($str){
    $_o=strrev($str);
    // echo $_o;
        
    for($_0=0;$_0<strlen($_o);$_0++){
       
        $_c=substr($_o,$_0,1);
        $__=ord($_c)+1;
        $_c=chr($__);
        $_=$_.$_c;   
    } 
    return str_rot13(strrev(base64_encode($_)));
}
$str=$_GET['var'];
$str=encode($str);
if ($str==$var) echo $flag;
else echo 'error';

highlight_file(__FILE__);
/*
   逆向加密算法，解密$var
*/
?>
