import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.List;
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
public class AuthorityTest {

    private UrlValidator validator;
    private URL url;

    public static final String BASE_AUTHORITY = "//www.test.com";

    public static final URLPart AUTHORITIES[] = {

            new URLPart(BASE_AUTHORITY, true),
            new URLPart("www.test.com", false),             // No forward slashes
            new URLPart("//0.0.0.0", true),                 // IP4 Address Lower Limit
            new URLPart("//255.255.255.255", true),         // IP4 Address Upper Limit
            new URLPart("//-1.-1.-1.-1", false),            // IP4 Address below limit
            new URLPart("//256.256.256.256", false),        // IP4 Address above limit
            new URLPart("//172.5.3", false),                // Short IP4 Address
            new URLPart("//172.5.3.189.4", false),          // Long IP4 Address

            new URLPart("//[0002:00FB:0000:0000:0000:0000:0000:0000]", true),       // IP6 address with valid hexadecimal address
            new URLPart("//[0002:00FB:GGGG:0000:1MNP:0000:0000:0000]", false),      // IP6 address with invalid hexadecimal characters
            new URLPart("//[0002:00FB:ABCD:BCDE:CDEF:1234:5678:90AB:0000]", false), // IP6 address with too many address blocks
            new URLPart("//[0002:00FB]", false),                                    // IP6 address with too few address blocks
            new URLPart("//[0000F:00FB:0000:0000:0000:0000:0000:0000]", false),     // IP6 address with too many characters in address
            new URLPart("//[1:FB:789:BCDE:C:a:5:865]", true),                       // IP6 address with variable address block lengths

            new URLPart("//www.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789.com", true),     // Test label limit
            new URLPart("//www.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789a.com", false),   // Test above label limit

            new URLPart("//www" + maxCharacterString() + ".com", true),          // Test max character limit
            new URLPart("//www" + maxCharacterString() + "a.com", false),        // Test above max character limit
            new URLPart("//www.]];,.12&*^jksdfhja+_)(*&^^$|.com", false),           // Test invalid characters

            new URLPart("//123.01234567890.456", false),    // Test all numeric
            new URLPart("//www.01234567890.com", true),     // Test not all numeric
    };

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(SchemeTest.BASE_SCHEME, BASE_AUTHORITY, PortTest.BASE_PORT, PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true, true, true );
    }

    @After
    public void teardown(){

        validator = null;
        url = null;
        authority = null;
    }

    @Parameterized.Parameter
    public URLPart authority;

    @Parameterized.Parameters(name= "Authority Test {0}")
    public static List<URLPart> authorityMutations() {

        return Arrays.asList(AUTHORITIES);
    }

    @Test
    public void testAuthority(){

        url.setAuthority(authority.getPart(), authority.isValid());
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }

    private static String maxCharacterString(){

        Random random = new Random();
        random.setSeed(System.nanoTime());

        final String validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

        final int CHAR_PER_LABEL_LIMIT = 63;
        final int CHAR_LIMIT = 253;

        StringBuilder authority = new StringBuilder(CHAR_LIMIT - 7);

        // Build a large string to test max characters
        for(int i = 0; i < authority.capacity(); i++){

            if(i % CHAR_PER_LABEL_LIMIT == 0){
                authority.append(".");
            } else {
                authority.append(validCharacters.charAt(random.nextInt(validCharacters.length())));
            }
        }

        return authority.toString();
    }
}
