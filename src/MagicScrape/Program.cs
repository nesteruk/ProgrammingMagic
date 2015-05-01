using System;
using System.Collections.Generic;
using WatiN.Core;

namespace MagicScrape
{
  class Program
  {
    private static string startPage = "http://gatherer.wizards.com/Pages/Search/Default.aspx?page={0}&set=[\"{1}\"]";
    private static string cardSet = "Magic 2015 Core Set";
    private static IE ie;

    [STAThread]
    static void Main(string[] args)
    {
      using (ie = new IE())
      {
        int currentPage = 1;
        string s;
        s = string.Format(startPage, currentPage, cardSet.Replace(" ", "%20"));
        ie.GoTo(s);
        int maxPage = ie.Div(Find.ByClass("pagingcontrols")).Links.Count - 2;
        var cardIds = new HashSet<string>();

        while (currentPage <= maxPage)
        {
          s = string.Format(startPage, currentPage, cardSet.Replace(" ", "%20"));
          ie.GoTo(s);

          var cardItemTable = ie.Table(Find.ByClass("cardItemTable"));

          var firstCell = cardItemTable.TableBodies[0].OwnTableRows[0]
            .TableCells[0];

          foreach (var t in firstCell.Tables)
          {
            var u = t.OwnTableBodies[0].OwnTableRows[0].OwnTableCells[1]
              .Divs[1].Spans[0].Links[0].Url;
            var id = u.Split('=')[1];
            cardIds.Add(id);
          }

          currentPage++;
        }

        foreach (var id in cardIds)
          ProcessCard(id);
      }
    }

    private static void ProcessCard(string id)
    {
      var url = "http://gatherer.wizards.com/Pages/Card/Details.aspx?printed=false&multiverseid=" + id;
      ie.GoTo(url);
    }
  }
}
