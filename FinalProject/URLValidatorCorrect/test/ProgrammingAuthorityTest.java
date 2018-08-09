import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Collection;
import java.util.Random;
import java.util.Arrays;

/**
 * Tests a URL, domain specific, with the following test rules:
 *
 * - Domain Name / IP Address Range - 0.0.0.0 to 255.255.255.255
 * - Domain Name must start with "//"
 * - Domain Name Range - 0 to 63 characters per label
 * - Domain Name Range - 253 characters total including labels and periods
 * - Domain Name Characters - letters (non-case sensitive), numbers and "-"
 * - Domain Name must not start or end with a "-"
 * - Domain Name must not be all numeric
 * - Domain must not be null
 */
@RunWith(Parameterized.class)
public class ProgrammingAuthorityTest {

    private static UrlValidator validator;
    private static URL url;
    private static final String AUTHORITY = "www.test.com";
    private static final String PRECURSOR = "//";

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL("http:", AUTHORITY, "", "", "",
                true, true, true, true, true );
    }

    @Parameterized.Parameter(0)
    public String authority;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Authority - {0}, Expected = {1}")
    public static Collection<Object[]> authorityMutations() {

        Object[][] data = new Object[18][2];

        final int IP4_LOWER_LIMIT = 0;
        final int IP4_UPPER_LIMIT = 255;
        final String VALID_IP6_CHARACTERS = "1234567890abcdef";
        final int CHAR_PER_LABEL_LIMIT = 63;
        final int CHAR_LIMIT = 253;

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // IP4 Address Lower Limit
        data[0][0] = PRECURSOR + IP4_LOWER_LIMIT + "." + IP4_LOWER_LIMIT + "."
                + IP4_LOWER_LIMIT + "." + IP4_LOWER_LIMIT;
        data[0][1] = true;

        // IP4 Address Upper Limit
        data[1][0] = PRECURSOR +IP4_UPPER_LIMIT + "." + IP4_UPPER_LIMIT + "."
                + IP4_UPPER_LIMIT + "." + IP4_UPPER_LIMIT;
        data[1][1] = true;

        // IP4 Address below limit
        data[2][0] = PRECURSOR +(IP4_LOWER_LIMIT - 1) + "." + IP4_LOWER_LIMIT
                + "." + IP4_LOWER_LIMIT + "." + IP4_LOWER_LIMIT;
        data[2][1] = false;

        // IP4 Address above limit
        data[3][0] = PRECURSOR +(IP4_UPPER_LIMIT + 1) + "." + IP4_UPPER_LIMIT
                + "." + IP4_UPPER_LIMIT + "." + IP4_UPPER_LIMIT;
        data[3][1] = false;

        // Short IP4 Address
        data[4][0] = PRECURSOR + "172.5.3";
        data[4][1] = false;

        // Long IP4 Address
        data[5][0] = PRECURSOR + "172.5.3.189.4";
        data[5][1] = false;

        // IP6 address with valid hexadecimal address
        data[6][0] = PRECURSOR + "[0002:00FB:0000:0000:0000:0000:0000:0000]";
        data[6][1] = true;

        // IP6 address with invalid hexadecimal address
        data[7][0] = PRECURSOR + "gh01.76bc.00fe.1290.gggg.cdea.1982.0100:";
        data[7][1] = false;

        // IP6 address with too many address blocks
        data[8][0] = PRECURSOR + "ab01.76bc.00fe.1290.bbbb.cdea.1982.0100.ab01:";
        data[8][1] = false;

        // IP6 address with too few address blocks
        data[9][0] = PRECURSOR + "abo1:";
        data[9][1] = true;

        // No forward slashes
        data[10][0] = AUTHORITY;
        data[10][1] = false;

        // Test label limit
        data[11][0] = PRECURSOR + "www.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789.com";
        data[11][1] = true;

        // Test above label limit
        data[12][0] = PRECURSOR + "www.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789a.com";
        data[12][1] = false;

        // Build a large string to test max characters
        StringBuilder authority = new StringBuilder(CHAR_LIMIT - 7);
        final String validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

        for(int i = 0; i < authority.capacity(); i++){

            if(i % CHAR_PER_LABEL_LIMIT == 0){
                authority.append(".");
            } else {
                authority.append(validCharacters.charAt(random.nextInt(validCharacters.length())));
            }
        }

        // Test max character limit
        data[13][0] = PRECURSOR + "www" + authority.toString() + ".com";
        data[13][1] = true;

        // Test above max character limit
        data[14][0] = PRECURSOR + "www" + authority.toString() + "a.com";
        data[14][1] = false;

        // Test invalid characters
        data[15][0] = PRECURSOR + "www." + "+]];,.12&*^jksdfhja+_)(*&^^$|" + ".com";
        data[15][1] = false;

        // Test all numeric
        data[16][0] = PRECURSOR + "123.01234567890.456";
        data[16][1] = false;

        // Test not all numeric
        data[17][0] = PRECURSOR + "www.01234567890.com";
        data[17][1] = true;

        return Arrays.asList(data);
    }

    @Test
    public void testAuthority(){

        url.setAuthority(authority, isValid);
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}
