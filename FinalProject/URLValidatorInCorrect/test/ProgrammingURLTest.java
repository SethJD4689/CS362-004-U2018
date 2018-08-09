import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class ProgrammingURLTest {

    private static UrlValidator validator;

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);
    }

    @Parameterized.Parameter
    public URL url;

    @Parameterized.Parameters(name= "{index}: url - {0}")
    public static List<Object> urlMutations() {

        /**
         * Tests a URL, scheme specific, with the following test rules:
         *
         * - Scheme must end with ":"
         * - Scheme must begin with a letter
         * - Scheme must only include letters, number, "+", ".", and "-"
         * - Scheme capitalization is
         * - Scheme must not be null
         * - Scheme has no length limits
         */

        URLPart[] schemes = {
                new URLPart("http:", true),
                new URLPart("https:", true),
                new URLPart("file:", true),
                new URLPart("8http:", false),
                new URLPart("", false),
                new URLPart("ftp", false),
                new URLPart("ST+.-:", true)
        };

        URLPart[] authorities = {
                new URLPart("//www.test.com", true),
                new URLPart("//google.com", true),
                new URLPart("[0002:00FB:0000:0000:0000:0000:0000:0000]", true)
        };

        URLPart[] ports = {
                new URLPart(":1234", true),
                new URLPart("", true)
        };

        URLPart[] paths = {
                new URLPart("", true)
        };

        URLPart[] queries = ProgrammingQueryTest.QUERIES;

        int tests = schemes.length * authorities.length * ports.length
                * paths.length * queries.length;
        Object[] data = new Object[tests];

        for(int s = 0; s < schemes.length && tests > 0; s++){

            for(int a = 0; a < authorities.length && tests > 0; a++){

                for(int po = 0; po < ports.length && tests > 0; po++){

                    for(int pa = 0; pa < paths.length && tests > 0; pa++){

                        for(int q = 0; q < queries.length && tests > 0; q++){

                            URL url = new URL();
                            url.setScheme(schemes[s].getPart(), schemes[s].isValid());
                            url.setAuthority(authorities[a].getPart(), authorities[a].isValid());
                            url.setPort(ports[po].getPart(), ports[po].isValid());
                            url.setPath(paths[pa].getPart(), paths[pa].isValid());
                            url.setQuery(queries[q].getPart(), queries[q].isValid());

                            if(url.getScheme().equals("file:") && url.getPort().contains(":")){

                                url.setPortIsValid(false);
                            }

                            data[tests - 1] = url;
                            tests --;
                        }
                    }
                }
            }
        }

        return Arrays.asList(data);
    }

    @Test
    public void testUrl(){

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        }catch(AssertionError e){

            System.out.println("FAILED: Expected - " + url.isURLValid()
                    + ", URL - " + url.getURL());

            throw e;
        }
    }
}


