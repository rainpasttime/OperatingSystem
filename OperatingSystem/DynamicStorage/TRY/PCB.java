/*
 * PCB类：
 *     成员：
 *        1.唯一的进程号
 *        2.进程名字
 *        3.进程状态
 *        4.进程等待原因
 *        5.进程运行所需时间（用一个整形代表需要几个时间片）
 *     方法：
 *        1.display:展示PCB的内容
 *        2.run:运行这个进程
 */
public class PCB {
	private int ID;
	private String name;
	private String status;
	private String reason;
	private int Time;
	
	public void display() {
		System.out.print("ID： "+ID+"   name："+name+"   status："+status+"   run time: "+Time);
		if(status=="Waiting") {
			System.out.println("   waiting reason："+reason);
		}
		else
			System.out.println("");
	}
	public int run(int count) {
		System.out.println("===========================================");
		System.out.println("======Run="+count+"===============================");
		Time-=1;
		if(Time==0) {
			status = "Finished";
			display();
		}
		return Time;
	}
	public void changeStatus(String s) {
		status = s;
	}
	public void addReason(String a) {
		reason = a;
	}
	public int getID() {
		return ID;
	}
	public String getName() {
		return name;
	}
	public String getStatus() {
		return status;
	}
	public PCB(int i,String na,int t) {
		ID = i;
		name = na;
		status = "Ready";
		Time = t;
	}
	public PCB() {
	}

}
