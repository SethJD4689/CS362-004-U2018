import org.junit.runners.Suite;
import org.junit.runner.RunWith;

@RunWith(Suite.class)
@Suite.SuiteClasses({
        ManualTest.class,
        ProgrammingGeneralSchemeTest.class,
        ProgrammingFileSchemeTest.class,
        ProgrammingAuthorityTest.class,
        ProgrammingPortTest.class,
        ProgrammingPathTest.class,
        ProgrammingQueryTest.class,
        ProgrammingIsValidTest.class,
        ProgrammingURLTest.class
})

public class TestSuite {

    public final static String BASE_SCHEME = "http:";
    public final static String BASE_AUTHORITY = "//www.test.com";
    public final static String BASE_PORT = "";
    public final static String BASE_PATH = "";


    /*
        // Base Test
        data[0][0] = QUERY;
        data[0][1] = true;

        // Query with beginning whitespace
        data[1][0] = "\n" + QUERY;
        data[1][1] = false;

        // Query with middle whitespace
        data[2][0] = "?test = query";
        data[2][1] = false;

        // Query with end whitespace
        data[3][0] = QUERY + "\t";
        data[3][1] = false;*/

}
