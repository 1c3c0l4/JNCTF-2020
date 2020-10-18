<?php
include "flag.php";
error_reporting(E_ALL & ~E_NOTICE);
//$username = mysql_real_escape_string($_POST['username']);
//$password = mysql_real_escape_string($_POST['password']);
$username = $_POST['username'];
$password = $_POST['password'];
$link = mysqli_connect('localhost','root','JNCTFPAss123','JNCTF');
$query ="SELECT username FROM users WHERE username='$username' AND password='$password' ";;//找到与输入用户名相同的信息，注意要取出的信息有两项
$res = mysqli_query($link,$query);
if($res) {
  if(mysqli_num_rows($res) > 0){
      $row = mysqli_fetch_assoc($res);
	  if($row['username']=='admin '){
		  echo "<script>alert('$flag')</script>";}
		else echo "<script>alert('login successfully but no flag');history.go(-1)</script>";
  
      return $row['username'];
}
else	echo "<script>alert('failed');history.go(-1)</script>";
}
else	echo "<script>alert('failed');history.go(-1)</script>";
include('login.html');?>