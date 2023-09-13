
public class Transaction implements Comparable<Transaction>{
	private int blockNumber;
	private int index;
	private int gasLimit;
	private long gasPrice;
	private String fromAdr;
	private String toAdr;
	
	/**
	 * Initializes all Transaction fields.
	 * 
	 * @param number
	 * @param index
	 * @param gasLimit
	 * @param gasPrice
	 * @param fromAdr
	 * @param toAdr
	 */
	public Transaction(int number, int index, int gasLimit, long gasPrice, String fromAdr, String toAdr) {
		this.blockNumber = number;
		this.index = index;
		this.gasLimit = gasLimit;
		this.gasPrice = gasPrice;
		this.fromAdr = fromAdr;
		this.toAdr = toAdr;
	}
	/**
	 * Get block number
	 * 
	 * @return Block number
	 */
	public int getBlockNumber() {
		return blockNumber;
	}
	/**
	 * Get index
	 * 
	 * @return Index
	 */
	public int getIndex() {
		return index;
	}
	/**
	 * Get gas limit
	 * 
	 * @return gas limit
	 */
	public int getGasLimit() {
		return gasLimit;
	}
	/**
	 * Get gas price
	 * 
	 * @return Gas price
	 */
	public long getGasPrice() {
		return gasPrice;
	}
	/**
	 * Get from address
	 * 
	 * @return From address
	 */
	public String getFromAddress() {
		return fromAdr;
	}
	/**
	 * Get to address
	 * 
	 * @return To address
	 */
	public String getToAddress() {
		return toAdr;
	}
	/**
	 * Convert wei to ETH.
	 * 
	 * @return cost of the transaction in ETH.
	 */
	public double transactionCost() {
		long transInWei = gasLimit * gasPrice;
		double transInETH = ( (double) transInWei / 1e18);
		return transInETH;
	}
	/**
	 * return an exact string
	 * 
	 * @return string with index & block number
	 */
	public String toString() {
		return "Transaction " + index + " for Block " + blockNumber;
	}
	/**
	 * Comparison based on the index of the Transaction.
	 * 
	 * @param t
	 * @return comparison value
	 */
	@Override
	public int compareTo(Transaction t) {
		int comparisonVal;
		Integer idxOne = t.getIndex();
		Integer idxTwo = getIndex();
		comparisonVal = idxTwo.compareTo(idxOne);
		
		return comparisonVal;
	}
}
