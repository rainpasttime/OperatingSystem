/*
 * 内存类：
 * 假定整个内存中只有20个单元的内存块。则空内存，阻塞队列1，阻塞队列2，阻塞队列3，就绪队列所有的Storage
 * 加起来的数目是20.
 *     成员：1.空内存
 *         2.阻塞队列1
 *         3.阻塞队列2
 *         4.阻塞队列3
 *         5.就绪队列
 *     方法：
 *         1.Initialize:初始化内存的方法,初始化之后，空内存块有20个Storage，阻塞队列1，
 *                      阻塞队列2，阻塞队列3，就绪队列都是空。
 *         2.display:内存快照，展示内存里面阻塞队列，就绪队列，还有空内存的情况。
 *         3.Apply：创建一个进程。申请一块PCB，当内存里面有空的内存块时，可以申请，否则报错。
 *         4.Unique:传入一个int型参数，代表进程号，方法作用是判断这个进程号是否是唯一的。唯一的返回true,否则返回false。
 *         5.ChangeToWait:把进程状态从运行态或者就绪态转为等待态。传入一个int型参数来表示等待的原因，根据不同的等待原因把进程放进不同的等待队列里面去。
 *         6.Run:运行一个进程。如果一个进程已经运行完成，就回收那一块内存，把这个内存加入EmptyLine。
 */
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;
public class internalStorage {
	private static LinkedList<Storage> EmptyLine;
	private static LinkedList<Storage> WaitingLineOne;
	private static LinkedList<Storage> WaitingLineTwo;
	private static LinkedList<Storage> WaitingLineThree;
	private static LinkedList<Storage> ReadyLine;
	
	public static void Initialize() {
		EmptyLine = new LinkedList<Storage>();
		WaitingLineOne = new LinkedList<Storage>();
		WaitingLineTwo = new LinkedList<Storage>();
		WaitingLineThree = new LinkedList<Storage>();
		ReadyLine = new LinkedList<Storage>();
		for(int i=0;i<20;i++) {
			Storage tem = new Storage();
			EmptyLine.add(tem);
		}
	}
	public static void display() {
		System.out.println("===========================================");
		int i = EmptyLine.size();
		System.out.println("The number of empty storage is "+i);
		System.out.println("");
		
		i = WaitingLineOne.size();
		System.out.println("The number of waiting line one is "+i);
		while(i>0) {
			Storage tem = WaitingLineOne.get(i-1);
			tem.display();
			i--;
		}
		System.out.println("");
		
		i = WaitingLineTwo.size();
		System.out.println("The number of waiting line two is "+i);
		while(i>0) {
			Storage tem = WaitingLineTwo.get(i-1);
			tem.display();
			i--;
		}
		System.out.println("");
		
		i = WaitingLineThree.size();
		System.out.println("The number of waiting line three is "+i);
		while(i>0) {
			Storage tem = WaitingLineThree.get(i-1);
			tem.display();
			i--;
		}
		System.out.println("");
		
		i = ReadyLine.size();
		System.out.println("The number of ready line is "+i);
		while(i>0) {
			Storage tem = ReadyLine.get(i-1);
			tem.display();
			i--;
		}
		System.out.println("");
	}
	
	public static void Apply(){
		int i = EmptyLine.size();
		if(i==0) {
			System.out.println("Fail!There is no empty storage!");
			return;
		}
		else {
			Storage tem = EmptyLine.removeFirst();
			int flag = 1;
			while(flag==1) {
				boolean judge;
				int ti;
				int j;
				Scanner read = new Scanner(System.in);
				
				System.out.println("Input the ID of PCB:");
				try {
					j = read.nextInt();
				    judge = Unique(j);
				    if(!judge){
				    	System.out.println("Fail!The ID of PCB is no unique!Input again!");
					    continue;
				    }
				}
				catch(Exception e) {
					System.out.println("Please input number!Input again");
					continue;
				}
				
				System.out.println("Input the running time of PCB:");
				try {
					ti = read.nextInt();
				}
				catch(Exception e) {
					System.out.println("Please input number!Input again");
					continue;
				}
			    flag = 0;
				System.out.println("Input the name of PCB");
				String na = read.next();
				tem.FillInPCB(j, na,ti);
				ReadyLine.add(tem);
			}
		}
	}
	public static boolean Unique(int i) {
		int number = WaitingLineOne.size();
		if(number!=0) {
			Iterator<Storage> iter = WaitingLineOne.iterator();
			while(iter.hasNext()) {
				Storage temone = iter.next();
				PCB temtwo  = temone.getContent();
			    int j = temtwo.getID();
			    if(i==j)
			    	return false;
			}
		}
		
		number = WaitingLineTwo.size();
		if(number!=0) {
			Iterator<Storage> iter = WaitingLineTwo.iterator();
			while(iter.hasNext()) {
				Storage temone = iter.next();
				PCB temtwo  = temone.getContent();
			    int j = temtwo.getID();
			    if(i==j)
			    	return false;
			}
		}
		
		number = WaitingLineThree.size();
		if(number!=0) {
			Iterator<Storage> iter = WaitingLineThree.iterator();
			while(iter.hasNext()) {
				Storage temone = iter.next();
				PCB temtwo  = temone.getContent();
			    int j = temtwo.getID();
			    if(i==j)
			    	return false;
			}
		}
		
		number = ReadyLine.size();
		if(number!=0) {
			Iterator<Storage> iter = ReadyLine.iterator();
			while(iter.hasNext()) {
				Storage temone = iter.next();
				PCB temtwo  = temone.getContent();
			    int j = temtwo.getID();
			    if(i==j)
			    	return false;
			}
		}
		return true;
	}

	public static boolean ChangeToWait(int reason,int IDofPCB) {
		Storage temone;
		PCB temtwo;
		int tem;
		int flag = 1;
		int i=0;
		switch(reason) {
		case 0:
			temone = ReadyLine.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					ReadyLine.remove(i);
					temone.changeStatus("Waiting");
					temone.addReason("Waiting for Input");
					WaitingLineOne.add(temone);
					return true;
				}
				else {
					if(i<ReadyLine.size()-1) {
						i++;
					    temone = ReadyLine.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		case 1:
			temone = ReadyLine.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					ReadyLine.remove(i);
					temone.changeStatus("Waiting");
					temone.addReason("Waiting for printer");
					WaitingLineTwo.add(temone);
					return true;
				}
				else {
					if(i<ReadyLine.size()-1) {
						i++;
					    temone = ReadyLine.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		case 2:
			if(ReadyLine.isEmpty())
				return false;
			temone = ReadyLine.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					ReadyLine.remove(i);
					temone.changeStatus("Waiting");
					temone.addReason("Waiting for another process");
					WaitingLineThree.add(temone);
					return true;
				}
				else {
					if(i<ReadyLine.size()-1) {
						i++;
					    temone = ReadyLine.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		}
		return false;
	}
	public static void Run(int count) {
		if(ReadyLine.size()!=0) {
			Storage tem = ReadyLine.getFirst();
			int i = tem.Run(count);
		    if(i==0) {
		    	Storage one = ReadyLine.removeFirst();
			    one.Recycle();
			    EmptyLine.add(one);
		    }
		    else {
		    	Storage one = ReadyLine.removeFirst();
		    	ReadyLine.addLast(one);
		    }
		}
}
	public static boolean IsEmpty() {
		int i = ReadyLine.size();
		int j = WaitingLineOne.size();
		int t = WaitingLineTwo.size();
		int w = WaitingLineThree.size();
		if(i==0 && j==0 && t==0 && w==0)
			return true;
		else
			return false;
	}
	public static boolean RevokeWait(int reason,int IDofPCB) {
		int i= 0;
		Storage temone;
		PCB temtwo;
		int tem;
		int flag = 1;
		switch(reason) {
		case 0:
			temone = WaitingLineOne.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					WaitingLineOne.remove(i);
					temone.changeStatus("Ready");
					ReadyLine.add(temone);
					return true;
				}
				else {
					if(i<WaitingLineOne.size()-1) {
						i++;
					    temone =WaitingLineOne.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		case 1:
			temone = WaitingLineTwo.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					WaitingLineTwo.remove(i);
					temone.changeStatus("Ready");
					ReadyLine.add(temone);
					return true;
				}
				else {
					if(i<WaitingLineTwo.size()-1) {
						i++;
					    temone =WaitingLineTwo.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		case 2:
			temone = WaitingLineThree.get(i);
			temtwo = temone.getContent();
			tem = temtwo.getID();
			while(flag==1) {
				if(tem==IDofPCB) {
					flag = 0;
					WaitingLineThree.remove(i);
					temone.changeStatus("Ready");
					ReadyLine.add(temone);
					return true;
				}
				else {
					if(i<WaitingLineThree.size()-1) {
						i++;
					    temone =WaitingLineThree.get(i);
					    temtwo = temone.getContent();
					    tem = temtwo.getID();
					}
					else
						break;
				}
			}
			break;
		}
		return false;
	}
	public static void Revoke() {
		int i = WaitingLineOne.size();
		int j = WaitingLineTwo.size();
		int t = WaitingLineThree.size();
		if(i!=0) {
			Storage one = WaitingLineOne.removeFirst();
			one.changeStatus("Ready");
			ReadyLine.add(one);
		}
		if(j!=0) {
			Storage one = WaitingLineTwo.removeFirst();
			one.changeStatus("Ready");
			ReadyLine.add(one);
		}
		if(t!=0) {
			Storage one = WaitingLineThree.removeFirst();
			one.changeStatus("Ready");
			ReadyLine.add(one);
		}
	}
}
