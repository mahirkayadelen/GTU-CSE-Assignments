import java.util.Map;

public class encryptor {
    private Map<Character, Map<Character, Character>> map;
    private String key;
    private String keystream = "";
    private String plain_text;
    private String cipher_text = "";

    public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
        this.map = _map;
        this.key = _key;
        this.plain_text = text;
    }

    public void encrypt() {
        // Do not edit this method
        generate_keystream();
        generate_cipher_text();
    }

    /**
     * Generates the keystream based on the plain text length and the key provided.
     */
    private void generate_keystream() {
		StringBuilder keystreamGenerator = new StringBuilder();
		int plainTextLength = plain_text.length();
		int keyLength = key.length();
	
		for (int index = 0; index < plainTextLength; index++) {
			keystreamGenerator.append(key.charAt(index % keyLength));
		}
		this.keystream = keystreamGenerator.toString();
	}

    /**
     * Generates the cipher text using the Vigenere cipher method.
     */
    private void generate_cipher_text() {
		StringBuilder cipherTextBuilder = new StringBuilder();
		for (int index = 0; index < plain_text.length(); index++) {
			char plainCharacter = plain_text.charAt(index);
			char keystreamCharacter = keystream.charAt(index);
			cipherTextBuilder.append(map.get(plainCharacter).get(keystreamCharacter));
		}
		this.cipher_text = cipherTextBuilder.toString();
	}

    /**
     * Returns the generated keystream.
     *
     * @return The keystream.
     */
    public String get_keystream() {
        return keystream;
    }

    /**
     * Returns the generated cipher text.
     *
     * @return The cipher text.
     */
    public String get_cipher_text() {
        return cipher_text;
    }
}
