<?php
include_once("config.php");
session_start();
if(isset($_SESSION['username']))
{
    header("Location: upload.php");
}
?>
<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/jquery-3.5.1.min.js"></script>
    <script src="js/bootstrap.bundle.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <title>登录</title>
</head>
<body>
    <div class="container">
        <form action="login.php" method="POST">
            <h1 class="text-center">登录</h1>
            <div class="form-group">
                <label for="username">用户名:</label>
                <input class="form-control" type="text" name="username" id="username" required>
            </div>
            <div class="form-group">
                <label for="password">密码:</label>
                <input class="form-control" type="password" name="password" id="password" required>
            </div>
            <input class="btn btn-primary form-control" type="submit"  name="login" value="登录">
        </form>
    <div>
</body>

<?php
if(isset($_POST['login']))
{
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connect failed: " . $conn->connect_error);
} 

function waf($sql){
    $blacklist = array('select','handler',' union','value','(',',','#','-',';','=','like','or\'','or ');
    foreach ($blacklist as $b){
        if (stristr($sql,$b))
            die('Hacker');
    }
}
$username = $_POST['username'];
$password = $_POST['password'];
waf($username);
waf($password);
$sql = "SELECT * FROM users where username='$username' and password='$password'";
#echo $sql;
$result = $conn->query($sql);
if ($result->num_rows > 0) {
    //Query Success，查询成功就作为 admin 登录
    $_SESSION['username']='admin';
    echo "<script>alert(\"登录成功\");</script>";
    header("Location: upload.php");
}
else
{
    echo "<script>alert(\"密码错误，请重新登录\");</script>";
}

}
?>