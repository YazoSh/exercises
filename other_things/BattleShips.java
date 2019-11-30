/*# Battle-ships-game
	Battel ships is a battle between the user and the computer
	each deploying there ships on a 10 x 10 grid and trying to guess where each other's ships are,
	the winner is first to destroy all the other players ships.
*/


import java.util.*;

class BattleShips
{
	public static int pS = 5 , cS = 5;
	public static void main(String[] args)
	{
		char[][] map = new char[10][10];
		intro(map);
		playerDeploy(map);
		computerDeploy(map);
		System.out.println("Let the battel begin");

		while(true){
			if(cS == 0){
				System.out.println("\nHooray you won the battel");
				break;
			}
			if(pS == 0){
				System.out.println("you lost");
				break;
			}

			pTurn(map);
			cTurn(map);
			printMap(map);
			score();
		}
		
	}

	public static void intro(char[][] map)
	{
		System.out.println("*** Welcome to Battel Ships game ****\n\nRight now you have no ships!!\n");
		for(int i = 0 ; i < 10 ; i++)
			Arrays.fill(map[i],' ');

		printMap(map);
	}

	public static void printMap(char[][] map)
	{
		System.out.println("   0123456789   ");
		for(int i = 0;i<10;i++)
		{
			System.out.print(i + " |");
			
			for(int j = 0;j<10;j++){
				if(map[j][i] == '1'){
					System.out.print('@');
					continue;
				}
				if(map[j][i] == '2'){
					System.out.print(' ');
					continue;
				}
				if(map[j][i] == '#'){
					System.out.print(' ');
					continue;
				}
				System.out.print(map[j][i]);
			}

			System.out.println("| " + i);
		}
		System.out.println("   0123456789   ");
	}

	public static void playerDeploy(char[][] map)
	{
		int x,y;
		Scanner input = new Scanner(System.in);
		for(int t = 0;t<5;)
		{
			System.out.print("Enter X coordinate for your ship: ");
			x = input.nextInt();
			System.out.print("Enter Y coordinate for your ship: ");
			y = input.nextInt();

			if(!(x <10 && y < 10)){
				System.out.println("index out of bonds!!!!");
				continue;
			}
			if(map[x][y] != ' '){
				System.out.println("you can\'t place a ship here!!!");
				continue;
			}

				map[x][y] = '1';
				t++;
			System.out.println("-----------------------------------");
		}
		System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n");
		printMap(map);
	}

	public static void computerDeploy(char[][] map)
	{
		System.out.println("\n\n\n\ncomputer is deploying ships!");
		Random rand = new Random();
		int x,y;
		for(int i = 1 ; i <= 5;)
		{
			x = rand.nextInt(10);
			y = rand.nextInt(10);
			if(map[x][y] != ' ')
				continue;
			else
			{
				map[x][y] = '2';
				System.out.println(i + ". ship is deployed!");
				i++;
			}
		}
		System.out.println("-----------------------------------\n\n");
		printMap(map);
	}

	public static void pTurn(char[][] map)
	{
		Scanner input = new Scanner(System.in);
		int x,y;
		System.out.println("\n\n\n\nYOUR TURN!!");
		while(true){
			System.out.print("Enter X coordinate: ");
			x = input.nextInt();
			System.out.print("Enter Y coordinate: ");
			y = input.nextInt();
			if(!(x < 10 && y < 10)){
				System.out.println("please enter a valid coordinate");
				continue;
			}
			if(map[x][y] == '!' || map[x][y] == 'x' || map[x][y] == '-'){
				System.out.println("you have already shot in that place retard!!");
				continue;
			}
			if(map[x][y] == '2'){
				System.out.println("Boom! You sunk the ship!");
				map[x][y] = '!';
				cS--;
				break;
			}
			if(map[x][y] == '1'){
				System.out.println("Oh no, you sunk your own ship :( RETARD!!!!!!");
				map[x][y] = 'x';
				pS--;
				break;
			}
			if(map[x][y] == ' ' || map[x][y] == '#'){
				System.out.println("Sorry, you missed");
				map[x][y] = '-';
				break;
			}
		}
		
	}

	public static void cTurn(char[][] map)
	{
		System.out.println("COMPUTER\'S TURN!!!!!");
		Random rand = new Random();
		int x,y;
		while(true)
		{
			x = rand.nextInt(10);
			y = rand.nextInt(10);
			if(map[x][y] == '#')
				continue;
			if(map[x][y] == '1')
			{
				map[x][y] = 'x';
				System.out.println("The Computer sunk one of your ships!");
				pS--;
				break;
			}
			if(map[x][y] == '2')
			{
				map[x][y] = '!';
				System.out.println("The Computer sunk one of its own ships");
				cS--;
				break;
			}
			if(map[x][y] == ' ')
			{
				map[x][y] = '#';
				System.out.println("Computer missed");
				break;
			}

		}
	}

	public static void score(){
		System.out.print("Your ships: "+ pS + " | Computer ships: " + cS + "\n-----------------------------------");
	}
}
