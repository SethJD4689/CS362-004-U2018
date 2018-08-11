import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

/*
 * Tests various URLs by input partition.
 */
@RunWith(Parameterized.class)
public class PartitionsTest {

    private UrlValidator validator;

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);
    }

    @After
    public void teardown(){

        validator = null;
    }

    @Parameterized.Parameter(0)
    public String url;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "[{index}] Expected: {1}, URL: {0}")
    public static Collection<Object[]> partitionMutations() {

        Object[][] data = new Object[18][2];

        // * INPUT PARTITION: Valid alpha-numeric characters
        data[0][0] = "http://www.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.com";
        data[0][1] = true;

        // * INPUT PARTITION: Valid special characters
        data[1][0] = "http://www.goo-._~:/?#[]@!$&'()*+,;=gle.com";
        data[1][1] = true;

        // * INPUT PARTITION: Invalid special character: back tic
        data[2][0] = "http://www.`.com";
        data[2][1] = false;

        // * INPUT PARTITION: Invalid special character: percent sign        
        data[3][0] = "http://www.%.com";
        data[3][1] = false;

        // * INPUT PARTITION: Invalid special character: caret
        data[4][0] = "http://www.^.com";
        data[4][1] = false;

        // * INPUT PARTITION: Invalid special character: double quote
        data[5][0] = "http://www.\".com";
        data[5][1] = false;

        // * INPUT PARTITION: Invalid special character: less than sign
        data[6][0] = "http://www.<.com";
        data[6][1] = false;

        // * INPUT PARTITION: Invalid special character: greater than sign
        data[7][0] = "http://www.>.com";
        data[7][1] = false;

        // * INPUT PARTITION: Invalid special character: open brace
        data[8][0] = "http://www.{.com";
        data[8][1] = false;

        // * INPUT PARTITION: Invalid special character: close brace
        data[9][0] = "http://www.}.com";
        data[9][1] = false;
        
        // * INPUT PARTITION: PORT NUMBER TOO LOW
        data[10][0] = "http://www.google.com:-1";
        data[10][1] = false;

        // * INPUT PARTITION: PORT NUMBER TOO HIGH.
        data[11][0] = "http://www.google.com:65536";
        data[11][1] = false;

        // * INPUT PARTITION: VALID PORT NUMBER (LOW)
        data[12][0] = "http://www.google.com:0";
        data[12][1] = true;
        
        // * INPUT PARTITION: VALID PORT NUMBER (HIGH)
        data[13][0] = "http://www.google.com:65535";
        data[13][1] = true;

        // * INPUT PARTITION: ALL LOWER CASE LETTERS
        data[14][0] = "http://www.google.com";
        data[14][1] = true;
        
        // * INPUT PARTITION: ALL UPPER CASE CHARACTERS
        data[15][0] = "HTTP://WWW.GOOGLE.COM";
        data[15][1] = true;
        
        // * INPUT PARTITION: DOUBLE-BYTE UNICODE CHARACTERS
        data[16][0] = "http://www.₱₲₳.com";
        data[16][1] = false;
        
        // * INPUT PARTITION: ESCAPED DOUBLE-BYTE UNICODE CHARACTERS
        data[17][0] = "http%3A%2F%2Fwww.%E2%82%B1%E2%82%B2%E2%82%B3.com%0D%0A";
        data[17][1] = true;
        
        return Arrays.asList(data);
    }

    @Test
    public void testURL(){

        try{

            assertEquals(isValid, validator.isValid(url));

        } catch(AssertionError e){

            System.out.println("FAILED PARTITION: " + e.getMessage() + ", URL - " + url);
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED PARTITION: " + e.getMessage() + ", URL - " + url);
            throw e;
        }
    }
}
