
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;
import org.jfree.ui.ApplicationFrame;


public class Main extends ApplicationFrame{
	
	private static final long serialVersionUID = 1L;
	public Main(String title) {
	      super(title); 
	      setContentPane(createDemoPanel());
	}
	// Pie Chart Methods
	private static PieDataset createDataset() {
		 
		 try {
			Blocks.readFile("ethereumP1data.csv");
			Blocks.sortBlocksByNumber();
			
			ArrayList<Blocks> allBlocks = new ArrayList<>(Blocks.getBlocks());
			String miner;
			
			ArrayList<String> uniqMiners = new ArrayList<String>();
			ArrayList<Integer> uniqMinersFreq = new ArrayList<Integer>();
		
			DefaultPieDataset dataset = new DefaultPieDataset();
			
			for (int i = 0; i < allBlocks.size(); ++i){
				miner = allBlocks.get(i).getMiner();
				if (!(uniqMiners.contains(miner))){
					uniqMiners.add(miner);
					uniqMinersFreq.add(1);
				}
				else{
					for (int j = 0; j < uniqMiners.size(); ++j){
						if (uniqMiners.get(j).equals(miner)){
							uniqMinersFreq.set(j, uniqMinersFreq.get(j) + 1);
						}
					}
				}
			}
			
			for(int i = 0; i < uniqMiners.size(); i++) {
				dataset.setValue(uniqMiners.get(i) + ": " + uniqMinersFreq.get(i).toString() , uniqMinersFreq.get(i));
			}
				 
			return dataset;    
				
		} catch (FileNotFoundException e) {
				e.printStackTrace();
		} catch (IOException e) {
				e.printStackTrace();
		} 
			return null;
	   } 
	private static JFreeChart createChart( PieDataset dataset ) {
	      JFreeChart chart = ChartFactory.createPieChart("Each Unique Miner and its frequency", dataset, false, true, false);
	      return chart;
	}
	public static JPanel createDemoPanel() {
		    JFreeChart chart = createChart(createDataset());
		    return new ChartPanel(chart);
		         
	}
	
	// Bar graph Methods
	private static CategoryDataset createDataSet2() throws FileNotFoundException, IOException {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			
			int input = Blocks.timeDiff(Blocks.getBlockByNumber(15049308), Blocks.getBlockByNumber(15049407));
			int hours = (input % 86400) / 3600 ;
			int minutes = ((input % 86400) % 3600) / 60;
			int seconds = ((input % 86400) % 3600) % 60;
			
			
			dataset.addValue(hours, "Hours", "15049308-15049407");
			dataset.addValue(minutes, "Minutes","15049308-15049407");
			dataset.addValue(seconds, "Seconds","15049308-15049407");
			
			input = Blocks.timeDiff(Blocks.getBlockByNumber(15049311), Blocks.getBlockByNumber(15049388));
			hours = (input % 86400) / 3600 ;
			minutes = ((input % 86400) % 3600) / 60;
			seconds = ((input % 86400) % 3600) % 60;
			 
			dataset.addValue(hours, "Hours", "15049311-15049388");
			dataset.addValue(minutes, "Minutes","15049311-15049388");
			dataset.addValue(seconds, "Seconds","15049311-15049388");
			
			/*input = Blocks.timeDiff(Blocks.getBlockByNumber(15049399), Blocks.getBlockByNumber(15049388));
			hours = (input % 86400) / 3600 ;
			minutes = ((input % 86400) % 3600) / 60;
			seconds = ((input % 86400) % 3600) % 60;
			 
			dataset.addValue(hours, "Hours", "15049399-15049388");
			dataset.addValue(minutes, "Minutes","15049399-15049388");
			dataset.addValue(seconds, "Seconds","15049399-15049388");*/

			return dataset;
			
		}
	
	// Line Graph Method
	private static CategoryDataset createDataSet3() throws FileNotFoundException, IOException {
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
		
		String avgCost = "Avg Transaction Cost";  
	    String lowCost = "Lowest Transaction Cost";
	    String highCost = "Higest Transaction Cost";
	    
	    int num = 15049322 - 15049308 ;
	    
	   for(int i = 0; i <= num; i++){
	  	  int blockNumber = 15049308 + i;
	  	  double avgTransactionCost = Blocks.getBlockByNumber(blockNumber).avgTransactionCost();
	  	  String bNum = String.valueOf(blockNumber);
	  	  dataset.addValue(avgTransactionCost, avgCost, bNum);
	    }
	  
	   for(int i = 0; i <= num; i++){
		  int blockNumber = 15049308 + i;
		  String bNum = String.valueOf(blockNumber);
		  
		  ArrayList<Transaction> bTrans = new ArrayList<Transaction>(Blocks.getBlockByNumber(blockNumber).getTransactions());
		  Collections.sort(bTrans);
		  double low = bTrans.get(0).transactionCost();
		  for(Transaction t: bTrans){
			  if(t.transactionCost() < low) {
				  low = t.transactionCost();
			  }
		  }
		  dataset.addValue(low, lowCost, bNum);
	  }
	  
	  for(int i = 0; i <= num; i++)
	  {
		  int blockNumber = 15049308 + i;
		  String bNum = String.valueOf(blockNumber);
		  
		  ArrayList<Transaction> bTrans = new ArrayList<Transaction>(Blocks.getBlockByNumber(blockNumber).getTransactions());
		  Collections.sort(bTrans);
		  double high = bTrans.get(bTrans.size() - 1).transactionCost();
		  for(Transaction t: bTrans)
		  {
			  if(t.transactionCost() > high)
			  {
				  high = t.transactionCost();
			  }
		  }
		  dataset.addValue(high, highCost, bNum);
	  }
	    return dataset; 
	}
	
	public static void main(String[] args) throws FileNotFoundException, IOException {
		
		JFrame frame = new JFrame("Project 5 - Emma Smith");
	    frame.setSize(400, 400);
		
	    // make combo box
	    String[] options = {"--Select chart--", "Unique Miners", "Transaction Cost", "Time Difference"};
	    JComboBox<String> navigation = new JComboBox<>(options);
	    
	    // make pie chart 
	    PieDataset pieDataSet = createDataset();
	    JFreeChart PieChart = ChartFactory.createPieChart("Each Unique Miner and its frequency", pieDataSet, false, true, false);
	    ChartPanel chartPane = new ChartPanel(PieChart);
	    chartPane.setPreferredSize(new Dimension(1000, 500));
	    
	    // make bar graph
	    CategoryDataset barDataSet = createDataSet2();
	    JFreeChart barChart = ChartFactory.createBarChart("Time Difference Between Blocks", "Blocks", "Time Units (hrs, mins, secs)", barDataSet, PlotOrientation.VERTICAL, true, true, false);
	    ChartPanel chartPane2 = new ChartPanel(barChart);
	    chartPane2.setPreferredSize(new Dimension(1000, 600));
	    
	    // make line graph
	    CategoryDataset lineGraphSet = createDataSet3();
	    JFreeChart lineGraph = ChartFactory.createLineChart("Transaction Cost of Blocks", "Block Number", "Transaction Cost (ETH)", lineGraphSet);
	    ChartPanel chartPane3 = new ChartPanel(lineGraph);
	    CategoryPlot p = lineGraph.getCategoryPlot();
	    chartPane3.setPreferredSize(new Dimension(1000, 600));
	    org.jfree.chart.axis.CategoryAxis axis = p.getDomainAxis();
	    Font font = new Font("Dialog", Font.PLAIN, 7);
	    axis.setTickLabelFont(font);
	    
	    // create panels laidout vertically
	    JPanel mainPanel = new JPanel();
	    mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
	    JPanel panel2 = new JPanel(); // panel for combobox - always visible
	    JPanel panel3 = new JPanel(); // panel for sliders (pie chart), check boxes (line graph), text fields & buttons (bar graph) 
	    JPanel panel4 = new JPanel(); // panel for piechart
	    JPanel panel5 = new JPanel(); // panel for bar graph
	    JPanel panel6 = new JPanel(); // panel for line graph
	    
	    //add combo box to the top of the main panel
	    panel2.add(navigation);
	    panel2.setVisible(true);
	    mainPanel.add(panel2);
	    frame.add(mainPanel);
	    frame.setVisible(true);
	    
	    // sliders for pie chart
	    JSlider slide1 = new JSlider();
	    JSlider slide2 = new JSlider();
	    Dimension d2 = slide2.getPreferredSize();
	    slide2.setPreferredSize(new Dimension(d2.width+100,d2.height+40));
	    Dimension d = slide1.getPreferredSize();
	    slide1.setPreferredSize(new Dimension(d.width+100,d.height+40));
	    
	    // check boxes for line graph
	    JCheckBox cb1 = new JCheckBox("Average Transaction Cost");
	    JCheckBox cb2 = new JCheckBox("Lowest Transaction Cost");
	    JCheckBox cb3 = new JCheckBox("Highest Transaction Cost");
	    
	    // Text field and buttons for bar graph
	    JTextField text1 = new JTextField();
	    JTextField text2 = new JTextField();
	    JButton button = new JButton(" Add ");
	    text1.setPreferredSize(new Dimension(200, 24));
	    text2.setPreferredSize(new Dimension(200, 24));
	   
	    // actionlistener for combobox - navigate between options
	    navigation.addActionListener(new ActionListener() {
		   public void actionPerformed(ActionEvent e) {
			   JComboBox boxChanged = (JComboBox) e.getSource();
			   String chartSelected = (String) boxChanged.getSelectedItem();
			   if (chartSelected.equalsIgnoreCase("--Select Chart--")){
				   panel3.setVisible(false);
				   panel4.setVisible(false);
				   panel5.setVisible(false);
				   panel6.setVisible(false);	   
			   }
			   // if unique miners is selected, display sliders & pie chart
			   if (chartSelected.equalsIgnoreCase("Unique Miners")) {
				   // set all components to invisible except sliders
				   text1.setVisible(false);
				   text2.setVisible(false);
				   button.setVisible(false);
				   cb1.setVisible(false);
				   cb2.setVisible(false);
				   cb3.setVisible(false);
				   
				   panel3.setVisible(false); 
				   panel4.setVisible(false); 
				   panel5.setVisible(false);
				   panel6.setVisible(false);
				   mainPanel.add(panel3);
				   mainPanel.add(panel4);
				    
				   int ss = 15049308;
				    
				   slide1.setMinimum((ss));
				   slide1.setMaximum(15049407);
				   slide1.setPaintTrack(true);
				   slide1.setPaintTicks(true);
				   slide1.setPaintLabels(true);
				   slide1.setMajorTickSpacing(25);
				   slide1.setMajorTickSpacing(5);
				    
				   slide2.setMinimum((ss+1));
				   slide2.setMaximum(15049407);
				   slide2.setPaintTrack(true);
				   slide2.setPaintTicks(true);
				   slide2.setPaintLabels(true);
				   slide2.setMajorTickSpacing(25);
				   slide2.setMajorTickSpacing(5);
				   
				   panel3.add(slide1);
				   panel3.add(slide2);
				    
				   panel4.add(chartPane);
				   panel3.setVisible(true); 
				   panel4.setVisible(true); 
				   slide1.setVisible(true);
				   slide2.setVisible(true);
			   }
			   if(chartSelected.equalsIgnoreCase("Transaction Cost")) {
				  //set all components to invisible except checkboxes  
				   text1.setVisible(false);
				   text2.setVisible(false);
				   button.setVisible(false);
				   slide1.setVisible(false);
				   slide2.setVisible(false);
				   
				   panel3.setVisible(false); 
				   panel4.setVisible(false);
				   panel5.setVisible(false);
				   
				   panel3.add(cb1);
				   panel3.add(cb2);
				   panel3.add(cb3);
				   panel3.setVisible(true);
				   
				   mainPanel.add(panel6);
				   panel6.add(chartPane3);
				   panel6.validate();
				   panel6.setVisible(true);
				   
				   panel3.setVisible(true); 
				   cb1.setVisible(true);
				   cb2.setVisible(true);
				   cb3.setVisible(true);
				   
			   }
			   if(chartSelected.equalsIgnoreCase("Time Difference")) {
				  // set all components invisible except button and text fields
				  
				   slide1.setVisible(false);
				   slide2.setVisible(false);
				   cb1.setVisible(false);
				   cb2.setVisible(false);
				   cb3.setVisible(false);
				   
				   panel3.setVisible(false); 
				   panel4.setVisible(false); 
				   panel6.setVisible(false);
				   
				   panel3.add(text1);
				   panel3.add(text2);
				   panel3.add(button);
				   
				   mainPanel.add(panel5);
				   panel5.add(chartPane2);
				   panel5.validate();
				   panel5.setVisible(true);
				   
				   panel3.setVisible(true);
				   text1.setVisible(true);
				   text2.setVisible(true);
				   button.setVisible(true);
			   }
		   }
	   }); 
	}	
}