using UnitTestDemo;
using Xunit;

namespace XUnitTestProject
{
    public class UnitTest1
    {
        [Fact]
        public void AdditionTest()
        {
            var cal = new Calculator();
            var result = cal.Addition(1, 2);
            Assert.Equal(3, result);
        }

        
        [Theory]
        [ExcelData(fileName: "TestCase.xls")]
        public void Test1(decimal x, decimal y, decimal except)
        {
            var cal = new Calculator();
            var result = cal.Addition(x, y);
            Assert.Equal(except, result);
        }
    }
}
