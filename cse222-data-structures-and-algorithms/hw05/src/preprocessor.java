public class preprocessor {
    private String initial_string;
    private String preprocessed_string;

    public preprocessor(String str) {
        this.initial_string = str;
    }

    /**
     * Preprocess the string by capitalizing and cleaning it.
     */
    public void preprocess() {
        // Do not edit this method
        capitalize();
        clean();
    }

    /**
     * Capitalizes the initial string by converting all letters to uppercase.
     */
    private void capitalize() {
        this.preprocessed_string = initial_string.toUpperCase();
    }

    /**
     * Removes non-letter characters from the preprocessed string.
     */
    private void clean() {
        this.preprocessed_string = preprocessed_string.replaceAll("[^A-Z]", "");
    }

    /**
     * Returns the preprocessed string.
     *
     * @return The preprocessed string.
     */
    public String get_preprocessed_string() {
        return preprocessed_string;
    }
}
