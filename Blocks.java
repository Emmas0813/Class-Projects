import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TimeZone;
import java.util.TreeSet;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigDecimal;
import java.text.SimpleDateFormat;

public class Blocks implements Comparable<Blocks>{

	private static final String COLUMN_DELIMITER = ",";
	private int number;
	private String miner;
	private long timestamp;
	private int transactionCount;
	private static ArrayList<Blocks> blocks = new ArrayList<>();
	private ArrayList<Transaction> transactions;
	
	
	/**
	 * Initializes no fields. 
	 * 
	 * When printed using the toString() method
	 * it should return "Empty Block" exactly.
	 *  
	 */
	public Blocks() {}
	/**
	 * Initializes the block number. 
	 * 
	 * When printed using the toString()
	 * method it should return "Block Number: number" exactly.
	 * 
	 * @param Block number
	 */
	public Blocks(int number) {
		
		this.number = number;
	}
	/**
	 * Initialize the Block number and miner address. 
	 * 
	 * When printed using the toString() method it should return 
	 * "Block Number: number Miner Address: miner" exactly.
	 * 
	 * @param Block number
	 * @param Block miner
	 */
	public Blocks(int number, String miner) {
	
		this.number = number;
		this.miner = miner;
	}
	/**
	 * Initialize the Block number, miner address, timestamp,
	 * and transaction count.
	 * 
	 * @param Block number
	 * @param Block miner
	 * @param Block timestamp
	 * @param Block transactions
	 * @throws IOException 
	 * @throws FileNotFoundException 
	 */
	public Blocks(int number, String miner, long timestamp, int transactionCount) throws FileNotFoundException, IOException {
		// TODO: initialize the transactions
		// ArrayList by calling the new readTransactions() method 
		// for the new data file "ethereumtransactions1.csv".
		this.number = number;
		this.miner = miner;
		this.timestamp = timestamp;
		this.transactionCount = transactionCount;
		readTransactions("ethereumtransactions1.csv");
	}
	/**
	 * Get block number. 
	 * 
	 * @return int block number
	 */
	public int getNumber() {
		return number;
	}
	/**
	 * Get miner address. 
	 * 
	 * @return string miner address
	 */
	public String getMiner() {
		return miner;
	}
	/**
	 * Get transaction count.
	 * 
	 * @return amount of transactions
	 */
	public int getTransactionCount() {
		return transactionCount;
	}
	/**
	 * Get copy of Block transactions.
	 * 
	 * @return copy of transactions
	 */
	public ArrayList<Transaction> getTransactions(){
		return new ArrayList<>(transactions);
		
	}
	/**
	 * Should return the String representation of the date / time of time stamp.
	 * 
	 * @return String date of timestamp
	 */
	public String getDate() {
		Date date = new Date(timestamp * 1000L);
		String pattern = "E, d MMMM yyyy HH:mm:ss z";
		SimpleDateFormat simpleFormat = new SimpleDateFormat(pattern);
		simpleFormat.setTimeZone(TimeZone.getTimeZone ("CST"));
		String newDate = simpleFormat.format(date);
		return newDate;
	}
	/**
	 * Get copied array list of blocks. 
	 * 
	 * @return copy of the blocks ArrayList
	 */
	public static ArrayList<Blocks> getBlocks(){
		@SuppressWarnings("unchecked")
		ArrayList<Blocks> clone = (ArrayList<Blocks>) blocks.clone();
		ArrayList<Blocks> copy = clone;
		return copy;
	}
	/**
	 * calculate number of unique miners and its frequency.
	 *  
	 */
	public static void calUniqMiners() {
		
		ArrayList<String> uniqueMinersList = new ArrayList<String>();
		ArrayList<Integer> frequencyList = new ArrayList<Integer>();
		int frequency = 1;
		
		for(int i = 0; i < blocks.size(); i++) {
			for(int j = i + 1; j < blocks.size(); ++j) {
				if(blocks.get(i).getMiner().equals(blocks.get(j).getMiner())){
					frequency++;
				}
			}
			if(!uniqueMinersList.contains(blocks.get(i).getMiner())) {
				uniqueMinersList.add(blocks.get(i).getMiner());
				frequencyList.add(frequency);
			}
			frequency=1;
		}
		
		uniqMinersToString(uniqueMinersList, frequencyList);
	
	}
	/**
	 * Print each unique miner and its frequency.
	 * 
	 * @param List of unique miners
	 * @param List of each unique miner's frequency
	 */
	public static void uniqMinersToString(ArrayList<String> uniqueMinersList, ArrayList<Integer> frequencyList) {
		System.out.println("Number of unique Miners: " + uniqueMinersList.size() + "\n");
		System.out.println("Each unique Miner and its frequency:");
		for(int i = 0; i < uniqueMinersList.size(); i++) {
			System.out.println("Miner Address: " + uniqueMinersList.get(i));
			System.out.println("Miner Frequency: " + frequencyList.get(i));
			System.out.println();
		}
	}
	/**
	 * Should return the difference between A's and B's Block number. 
	 * 
	 * @param Block A
	 * @param Block B
	 * @return integer difference of the two blocks (+ or -).
	 */
	public static int blockDiff(Blocks A, Blocks B) {
		int a = A.getNumber();
		int b = B.getNumber();
		
		return Math.subtractExact(a, b);
	}
	/**
	 * Read from the file that corresponds to the given Block number. 
	 * 
	 * @param number passed to get block by.
	 * @return Blocks object 
	 */
	public static Blocks getBlockByNumber(int Num){
		for(int i = 0; i < blocks.size() - 1; i++) {
			if(Num == blocks.get(i).getNumber()){
				return blocks.get(i);
			}
		}
		return null;
	}
	/**
	 * Call different toStrings dependent on the constructor it is passed through. 
	 * 
	 * @return String based on constructor.
	 */
	public String toString() {
		if((number == 0) && (miner == null)) {
			return "Empty Block";
		}
		if(miner == null) {
			return "Block Number: " + number;
		}
		else { 
			return "Block Number: " + number + " Miner Address: " + miner;
		}
	}
	/**
	 * Read the file: "ethereumP1data.txt" 
	 * 
	 * @param String filename
	 */
	public static void readFile(String filename) throws FileNotFoundException, IOException {
		blocks.clear();
		BufferedReader br = new BufferedReader(new FileReader(filename));
		String[] blockInfo;
		String line;
		try {
			while((line = br.readLine()) != null) {
				blockInfo = line.split(COLUMN_DELIMITER);
				int number = Integer.parseInt(blockInfo[0]);
				String miner = blockInfo[9];
				int transactions = Integer.parseInt(blockInfo[17]);
				long timestamp = Long.parseLong(blockInfo[16]);
				Blocks block = new Blocks(number, miner, timestamp, transactions);
				blocks.add(block);
			} br.close();
		} catch(Exception e) {}
		
		
	}
	/**
	 * Should sort your blocks ArrayList in ascending order based on Block number.
	 * 
	 */
	public static void sortBlocksByNumber(){
		Collections.sort(blocks);
	}
	/**
	 * Should take two Blocks as input, and print to the console the 
	 * difference in their times in hours, minutes, and seconds
	 * 
	 * @param first Block
	 * @param second Block
	 */
	public static void timeDiff(Blocks first, Blocks second) {
		if(first == null || second == null) {
			System.out.println("A given Block is null.");
		}
		else {
			long t1 = first.timestamp;
			long t2 = second.timestamp;
			int t3 = (int) Math.abs(t2-t1);
			int hours = t3 / 3600;
			int minutes = (t3 % 3600) / 60;
			int seconds = t3 % 60;
			
			if(hours == 1 && minutes != 1 && seconds != 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hour, " + minutes + " minutes, and " + seconds + " seconds.");
			} else if(minutes == 1 && hours != 1 && seconds !=1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hours, " + minutes + " minute, and " + seconds + " seconds.");
			} else if(seconds == 1 && hours != 1 && seconds != 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hours, " + minutes + " minutes, and " + seconds + " second.");
			} else if(hours == 1 && minutes == 1 && seconds != 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hour, " + minutes + " minute, and " + seconds + " seconds.");
			} else if(hours == 1 && seconds == 1 && minutes != 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hour, " + minutes + " minutes, and " + seconds + " second.");
			} else if(minutes == 1 && seconds == 1 && hours != 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hours, " + minutes + " minute, and " + seconds + " second.");
			} else if (hours == 1 && minutes == 1 && seconds == 1) {
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hour, " + minutes + " minute, and " + seconds + " second.");
			}
			else{
				System.out.println("The difference in time between Block " + first.getNumber() + " and Block " + second.getNumber() +
						" is " + hours + " hours, " + minutes + " minutes, and " + seconds + " seconds.");
			}		
		}
	}
	
	/**
	 * Should take two Blocks as input, and calculate the total transactions 
	 * of the Blocks between those two Blocks
	 * 
	 * @param first Block
	 * @param second Block
	 * @return integer difference between blocks
	 */
	public static int transactionDiff(Blocks first, Blocks second) {
		sortBlocksByNumber();
		int sum = 0;
		if(second == null || first == null || second.equals(first) || (second.getNumber() < first.getNumber()) ) {
			return -1;
		}
		for(int i = (blocks.indexOf(first) + 1); i < blocks.indexOf(second); i++) {
			sum += blocks.get(i).getTransactionCount();
		}
		
		return sum;
	}
	/**
	 * compare blocks
	 * 
	 * @param Block to be compared
	 * @return integer comparison value
	 */
	@Override
	public int compareTo(Blocks o) {
		int comparisonVal;
		Integer blockNum = o.getNumber();
		Integer ogBlockNum = getNumber();
		comparisonVal = ogBlockNum.compareTo(blockNum);
		
		return comparisonVal;
	}
	/**
	 * Read columns from the data file in order to fill the 
	 * transactions ArrayList with Transaction objects by using the Transaction constructor.
	 * 
	 * @param filename
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	private void readTransactions(String filename) throws FileNotFoundException , IOException{
		File file = new File(filename);
		TreeSet<Transaction> transactionList = new TreeSet<Transaction>();
		Scanner sc = new Scanner(file);
		String[] transInfo;
		
		while(sc.hasNextLine()) {
			String line = sc.nextLine();
			transInfo = line.trim().split(COLUMN_DELIMITER);
			int number = Integer.parseInt(transInfo[3]);
			int index = Integer.parseInt(transInfo[4]);
			int gasLimit = Integer.parseInt(transInfo[8]);
			String fromAdr = transInfo[5];
			String toAdr = transInfo[6];
			BigDecimal longNumber = new BigDecimal(transInfo[9]);
			if(number == this.number) {
				transactionList.add(new Transaction(number, index, gasLimit, longNumber.longValue(), fromAdr, toAdr));
			}
		}
		transactions = new ArrayList<>(transactionList);
		sc.close();
	}
	/**
	 * Calculate the average transaction cost
	 * 
	 * @return average transaction cost
	 */
	public double avgTransactionCost() {
		double sum = 0;
		for (int i = 0; i < transactions.size(); i++) {
			sum += transactions.get(i).transactionCost();
		}
		double avg = sum / transactions.size();
		return avg;
	}
	/**
	 * Prints each unique from Address and its corresponding toAddress as well as its total transactions cost.
	 * 
	 */
	public void uniqFromTo() {
		
		System.out.println("Each transaction by from address for Block " + this.getNumber() + ": ");
		System.out.println();
		
		ArrayList<String> fromAdr = new ArrayList<>();
		
		for(Transaction t : transactions) {
			if(!fromAdr.contains(t.getFromAddress())) {
				fromAdr.add(t.getFromAddress());
			}
		}
		for(String a : fromAdr) {
			double cost = 0;
			System.out.println("From " + a);
			
			for(Transaction t : transactions) {
				if(t.getFromAddress().equals(a)) {
					System.out.println(" -> " + t.getToAddress());
					cost += t.transactionCost();
				}
			}
			
			System.out.println("Total cost of transactions: " + String.format("%.8f", cost) + " ETH");
			System.out.println();
		}
	}
}


