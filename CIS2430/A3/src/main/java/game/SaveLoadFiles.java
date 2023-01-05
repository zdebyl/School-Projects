package game;

import boardgame.Saveable;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.io.IOException;

public class SaveLoadFiles {
    /**
     * saves file
     * @param save saveable variable to implement saving
     * @param fileName name of the file to save to
     * @param pathLocation path location of the file to save to
    */
    public static void save(Saveable save, String fileName, String pathLocation) {
        Path path = FileSystems.getDefault().getPath(pathLocation);
        String fileToSave;

        fileToSave = save.getStringToSave();

        try {
            Files.writeString(path, fileToSave);
        } catch(IOException e) {
            throw new IllegalArgumentException("Error with file.");
        }
    }

    /**
     * loads file
     * @param load saveable variable to implement loading
     * @param fileName name of the file to load from
     * @param pathLocation path location of the file to load from
    */
    public static void load(Saveable load, String fileName, String pathLocation) {
        Path path = FileSystems.getDefault().getPath(pathLocation);
        String fileInfo;

        try {
            fileInfo = Files.readString(path);
            load.loadSavedString(fileInfo);
        } catch(IOException e) {
            throw new IllegalArgumentException("Error with file.");
        } catch(IllegalArgumentException e) {
            throw e;
        }
    }
}