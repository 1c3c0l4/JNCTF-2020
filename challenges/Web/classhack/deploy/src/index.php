<?php
highlight_file(__FILE__);
require "flag.php";

function filter($s){
    
    return str_replace("Hack","",$s);
}

class A{
    public $a;
    public $b;

    public function __construct($a,$b)
    {
        $this->a = $a;
        $this->b = $b;
    }
}

class B{
    public $key;
    public $xnum;

    function __destruct()
    {
        if($this->key === 'admin')
        {
            if($this->xnum<10 && strlen($this->xnum)>3)
            {
                global $flag;
                echo $flag;
            }
        }
    }
}

$x = new A($_GET['a'],$_GET['b']);
$y = unserialize(filter(serialize($x)));
?>