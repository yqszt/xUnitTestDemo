using System;
using System.Collections.Generic;
using System.Data;
using System.IO;

namespace UnitTestDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            var cal = new Calculator();
            var result = cal.Addition(1, 2);
        }
    }
}
