import java.util.Iterator;
import java.util.Map;

public class decryptor {
    private Map<Character, Map<Character, Character>> map;
    private String key;
    private String keystream = "";
    private String plain_text = "";
    private String cipher_text;

    public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
        this.map = _map;
        this.key = _key;
        this.cipher_text = text;
    }

    public void decrypt() {
        // Do not edit this method
        generate_keystream();
        generate_plain_text();
    }

    /**
     * Generates the keystream based on the cipher text length and the key provided.
     */
    private void generate_keystream() {
		StringBuilder keystreamGenerator = new StringBuilder();
		int cipherTextLength = cipher_text.length();
		int keyLength = key.length();
	
		for (int index = 0; index < cipherTextLength; index++) {
			keystreamGenerator.append(key.charAt(index % keyLength));
		}
		this.keystream = keystreamGenerator.toString();
	}

    /**
     * Generates the plain text using the Vigenere cipher method.
     * Uses an iterator with map.get(x).keySet().
     */
    private void generate_plain_text() {
		StringBuilder plainTextBuilder = new StringBuilder();
		for (int index = 0; index < cipher_text.length(); index++) {
			char cipherCharacter = cipher_text.charAt(index);
			char keystreamCharacter = keystream.charAt(index);
			Iterator<Character> keyIterator = map.get(keystreamCharacter).keySet().iterator();
			while (keyIterator.hasNext()) {
				char plainCharacter = keyIterator.next();
				if (map.get(keystreamCharacter).get(plainCharacter) == cipherCharacter) {
					plainTextBuilder.append(plainCharacter);
					break;
				}
			}
		}
		this.plain_text = plainTextBuilder.toString();
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
     * Returns the generated plain text.
     *
     * @return The plain text.
     */
    public String get_plain_text() {
        return plain_text;
    }
}
