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
        [InlineData(1, 2, 3)]
        [InlineData(100, 1000, 1100)]
        [InlineData(-1, 2, 1)]
        public void AdditionTest1(decimal x, decimal y, decimal except)
        {
            var cal = new Calculator();
            var result = cal.Addition(x, y);
            Assert.Equal(except, result);
        }


        [Theory]
        [ExcelData(fileName: @"TestCases/AdditionTestCase.xls")]
        public void AdditionTest2(decimal x, decimal y, decimal except)
        {
            var cal = new Calculator();
            var result = cal.Addition(x, y);
            Assert.Equal(except, result);
        }
    }
}
