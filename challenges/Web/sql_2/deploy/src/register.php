<?php
error_reporting(E_ALL & ~E_NOTICE);
$link = mysqli_connect('localhost','root','JNCTFPAss123','JNCTF');
$username = mysqli_real_escape_string($link,$_POST['username']);
$password = mysqli_real_escape_string($link,$_POST['password']);
if (mysqli_connect_errno($link)) 
{ 
    echo "连接 MySQL 失败: " . mysqli_connect_error(); 
} 
$query = mysqli_query($link,"SELECT * FROM users WHERE username = '$username'");
$res = mysqli_query($link,"SELECT * FROM users WHERE username = '$username'");
if($res) {
  if(mysqli_num_rows($res) > 0) {
	  echo "<script>alert('failed');history.go(-1)</script>";
  }
  else {
    $query = mysqli_query($link,"INSERT INTO users(username,password) VALUES ('$username','$password')");}
	echo "<script>alert('successfully')</script>";
}
include('register.html');?>