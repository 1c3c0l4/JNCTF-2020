<html xmlns="http://www.w3.org/1999/xhtml">

	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

		<title>当然是文件上传</title>

	</head>

	<body class="home">
<div class="body_padded">
	<h1>请上传图片</h1>

	

	<div class="vulnerable_code_area">
		<form enctype="multipart/form-data" action="#" method="POST">
			<input type="hidden" name="MAX_FILE_SIZE" value="100000" />
			选择图片上传:<br /><br />
			<input name="uploaded" type="file" /><br />
			<br />
			<input type="submit" name="Upload" value="Upload" />

		</form>
		
	</div>

	</body>

</html>

<?php 
error_reporting(0);

if( isset( $_POST[ 'Upload' ] ) ) {
    $target_path  = "./upload"; 
    $target_path .= basename( $_FILES[ 'uploaded' ][ 'name' ] ); 
    $uploaded_name = $_FILES[ 'uploaded' ][ 'name' ]; 
    $uploaded_type = $_FILES[ 'uploaded' ][ 'type' ]; 
    $uploaded_size = $_FILES[ 'uploaded' ][ 'size' ];
    if( ( $uploaded_type == "image/jpeg" || $uploaded_type == "image/png" ) && 
        ( $uploaded_size < 100000 ) ) { 

        if( !move_uploaded_file( $_FILES[ 'uploaded' ][ 'tmp_name' ], $target_path ) ) { 
            echo '<pre>上传失败。</pre>'; 
        } 
        else { 
            echo "<pre>{$target_path} 上传成功。</pre>"; 
        } 
    } 
    else {
        echo '<pre>文件上传失败，请上传jpg或png文件。</pre>'; 
    } 
} 

?> 
