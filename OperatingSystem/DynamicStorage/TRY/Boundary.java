/*
 * ���������ࣺ
 *        1.display��ÿ��ִ����һ���������ʾһ�飬���û�������һ����ʲô
 *        2.WaitingReason:���û�����Ҫ��һ��ϵͳ����ȴ����е�ʱ����ʾ���������ʾ�û�����ȴ���ԭ��͵ȴ��Ľ��̺�
 *        3.InputID:������ʾ�û�������̺�
 */
import java.util.Scanner;
public class Boundary {
	public static int display() {
		System.out.println("===========================================");
		System.out.println("0:Exit  1:add PCB  2:add waitintg line 3:display 4��revoke waiting ");
		Scanner read = new Scanner(System.in);
		int i = 0;
		try {
		i = read.nextInt();
		}
		catch(Exception e) {
			System.out.println("Input number!");
			return -1;
		}
		if(i==0)
			read.close();
		return i;
	}
	
	public static int WaitingReason() {
		int i = 0;
		System.out.println("===========================================");
		System.out.println("0:Wating for input  1:Waiting for printer  2:Waiting for another process");
		Scanner read = new Scanner(System.in);
		try {
		i = read.nextInt();
		}
		catch(Exception e) {
			System.out.println("Input number!Input again!");
			return -1;
		}
		if(i<0||i>3) {
			System.out.println("Wrong!input the number in list!");
			return -1;
		}
		return i;
	}
	
	public static int InputID() {
		Scanner read = new Scanner(System.in);
		System.out.println("Input the ID of the process!");
		int i = read.nextInt();
		return i;
	}

}