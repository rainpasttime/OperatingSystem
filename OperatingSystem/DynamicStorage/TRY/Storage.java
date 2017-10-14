/*
 * һ���洢��Ԫ�ࣺ
 *           ��Ա��
 *              1.flag���ж�����ڴ���Ƿ��ǿյ�
 *              2.content���洢PCB����
 *           ������
 *              1.FillInPCB��������ڴ���ǿյģ����ڴ��ȡ����ʹ��
 *              2.Run:������һ���ڴ汣��Ľ���
 *              3.Recycle:������һ���ڴ棬�ڽ����������֮�󱻵���
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
