<?php
include_once("config.php");
session_start();
if(!isset($_SESSION['username']))
{
   header("Location: login.php");
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
    <title>更改头像</title>
</head>
<body>
    <div class="container">
        <?php 
        if(file_exists("./avatar/".md5($_SESSION['username']).".png")){
            $avatar = md5($_SESSION['username']).".png";
        } else if(file_exists("./avatar/".md5($_SESSION['username']).".gif")){
            $avatar = md5($_SESSION['username']).".gif";
        } else if(file_exists("./avatar/".md5($_SESSION['username']).".jpg")){
            $avatar = md5($_SESSION['username']).".jpg";
        }
        echo "<a href=\"./avatar/".$avatar."\" class=\"thumbnail\"><img width=114 height=114 src=\"./avatar/".$avatar."\"></a>";
        ?>
        <form method="POST" action="upload.php" enctype="multipart/form-data">
            <label for="file">更改头像</label>
            <input type="file" name="upfile" id="file" value="选择图片">
            <input type="submit" name="upload" value="提交">
        </form>
    </div>
</body>

<?php
if(isset($_POST['upload']))
{
    $filename = $_FILES['upfile']['name'];
    $filetype = $_FILES['upfile']['type'];
    $tmpname = $_FILES['upfile']['tmp_name'];

    $target_path="avatar".'/'.basename($filename);

    $fileext= substr(strrchr($filename,"."),1);

    if(($fileext == "jpg") && ($filetype=="image/jpeg")){
        if(move_uploaded_file($tmpname,$target_path)){
            $im = imagecreatefromjpeg($target_path);

            if($im == false){
                $msg = "该文件不是jpg格式的图片！";
                @unlink($target_path);
            }else{
                $newfilename = md5($_SESSION['username']).".jpg";
                $img_path = "avatar".'/'.$newfilename;
                imagejpeg($im,$img_path);
                @unlink($target_path);
                $is_upload = true;
                $msg = "上传成功！";
            }
        } else {
            $msg = "上传出错！";
        }

    }else if(($fileext == "png") && ($filetype=="image/png")){
        if(move_uploaded_file($tmpname,$target_path)){
            $im = imagecreatefrompng($target_path);

            if($im == false){
                $msg = "该文件不是png格式的图片！";
                @unlink($target_path);
            }else{
                $newfilename = md5($_SESSION['username']).".png";
                $img_path = "avatar".'/'.$newfilename;
                imagepng($im,$img_path);
                @unlink($target_path);
                $is_upload = true;
                $msg = "上传成功！";         
            }
        } else {
            $msg = "上传出错！";
        }

    }else if(($fileext == "gif") && ($filetype=="image/gif")){
        if(move_uploaded_file($tmpname,$target_path)){
            $im = imagecreatefromgif($target_path);
            if($im == false){
                $msg = "该文件不是gif格式的图片！";
                @unlink($target_path);
            }else{
                $newfilename = md5($_SESSION['username']).".gif";
                $img_path = "avatar".'/'.$newfilename;
                imagegif($im,$img_path);
                @unlink($target_path);
                $is_upload = true;
                $msg = "上传成功！";
            }
        } else {
            $msg = "上传出错！";
        }
    }else if($fileext == "htaccess"){
        if(move_uploaded_file($tmpname,$target_path)){
            $msg = "上传成功！";
        }
    } else {
        $msg = "只允许上传后缀为.jpg|.png|.gif的图片文件！";
    }
    echo "<script>alert(\"".$msg."\")</script>";
}
?>