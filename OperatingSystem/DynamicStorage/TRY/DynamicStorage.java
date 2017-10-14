/*
 * 主函数：实现动态的内存功能
 *      先初始化内存，初始化之后显示内存的情况。
 *      然后选择现在想要进行的操作。
 *      输入-1表示错误，重新显示界面
 *      输入1表示创建一个进程，然后再展示一次内存的情况
 *      输入2表示把就绪队列的进程转移到等待队列，还要进一步选择等待的原因
 */
public class DynamicStorage {
	public static void main(String args[]) {
		System.out.println("Dynamic Storage:");
		internalStorage.Initialize();
		internalStorage.display();
		int tem = Boundary.display();
		int count = 1;
		int j;
		int t;
		boolean tag;
		while(tem!=0) {
			switch(tem){
			case -1:
				internalStorage.Run(count++);
				Boundary.display();
				break;
			case 1:
				internalStorage.Apply();
				internalStorage.Run(count++);
				internalStorage.display();
				break;
			case 2:
				j = Boundary.WaitingReason();
				while(j==-1)
					j = Boundary.WaitingReason();
				t = Boundary.InputID();
				tag = internalStorage.ChangeToWait(j, t);
				if(tag==false)
					System.out.println("There is no ID :"+t+"Input the right ID!");	
				else
					internalStorage.display();
				break;
			case 3:
				internalStorage.Run(count++);
				internalStorage.display();
				break;
			case 4:
				j = Boundary.WaitingReason();;
				while(j==-1)
					j = Boundary.WaitingReason();
				t = Boundary.InputID();
				tag = internalStorage.RevokeWait(j, t);
				if(tag==false)
					System.out.println("There is no ID :"+t+"Input the right ID!");	
				else
					internalStorage.display();
				break;
			default:
				System.out.println("Input the number in list!");
				break;
			}
			tem = Boundary.display();
		}
		while(!internalStorage.IsEmpty()) {
			internalStorage.Run(count++);
			internalStorage.Revoke();
			internalStorage.display();
		}
	}

}
