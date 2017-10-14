/*
 * 一个存储单元类：
 *           成员：
 *              1.flag：判断这个内存块是否是空的
 *              2.content：存储PCB内容
 *           方法：
 *              1.FillInPCB：当这个内存块是空的，把内存块取出来使用
 *              2.Run:运行这一块内存保存的进程
 *              3.Recycle:回收这一个内存，在进程运行完成之后被调用
 *              
 */
public class Storage {
	private int flag = 0;
	private PCB content;
	
	public void FillInPCB(int i,String na,int t) {
		flag = 1;
		content = new PCB(i,na,t);
	}
	public int Run(int count) {
		int i = content.run(count);
		return  i;
	}
	public void Recycle() {
		flag = 0;
		content = new PCB();
	}
	public int getFlag() {
		return flag;
	}
	public PCB getContent() {
		return content;
	}
	public void display() {
		content.display();
	}
	public void changeStatus(String s) {
		content.changeStatus(s);
	}
	public void addReason(String a) {
		content.addReason(a);
	}

}
