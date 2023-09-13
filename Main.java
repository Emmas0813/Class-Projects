package application;
	
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.TilePane;


public class Main extends Application {
	@Override
	public void start(Stage stage) {
		try {
			stage.setTitle("Emma Smith - Prpject 5");
			TilePane r = new TilePane();
			Label description_label = new Label("Combo Box");
			
			String[] options = {"--Select chart--", "Unique Miners", "Transaction Cost", "Time Difference"};
			
			ComboBox cbox = new ComboBox(FXCollections.observableArrayList(options));
			
			TilePane tp = new TilePane(cbox);
			Scene scene = new Scene(cbox, 200, 200);
			stage.setScene(scene);
			stage.show();
			
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
