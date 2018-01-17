内联钩子
--------
VS2017+WIN10测试成功

1.正常弹框“HOOK流程” 

2.被HOOK之后，弹框“HOOK流程”+“被HOOK了1”（实际执行MyMessageBox）

3.再次调用MessageBox(实际执行MyMessageBox)，弹框“HOOK流程”+“被HOOK了2”

4.调用Unhook

5.正常调用MessageBox,弹框正常流程
