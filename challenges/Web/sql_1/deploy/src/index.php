<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <title>easy_sql_injection</title>
</head>
<body>
<h1>一次简单的sql注入</h1>
<form method="get">
    来吧:<input type="text" name="inject" >
    <input type="submit">
</form>


</body>
</html>
<?php

if( isset( $_GET[ 'inject' ] ) ) {
    // Get input
    $server="localhost";//主机的IP地址，你也可以选填127.0.0.1
    $db_username="root";//数据库用户名
    $db_password="JNCTFPAss123";//数据库密码

    $con = mysqli_connect($server,$db_username,$db_password);//链接数据库
    mysqli_select_db($con,'sql_injection');
    $id = $_GET[ 'inject' ];

    // Check database
    $query  = "SELECT user_name FROM Flag WHERE id = '$id';";
    $result = mysqli_query($con,  $query ) or die( '<pre>' . mysqli_error().'</pre>' );

    // Get results
    while( $row = mysqli_fetch_assoc( $result ) ) {
        // Get values
        $user_name = $row["user_name"];
        //$flag  = $row["flag"];

        // Feedback for end user
        echo "<pre>ID: {$id}<br />First name: {$user_name}</pre>";
    }

    mysqli_close($con);
}

?> 