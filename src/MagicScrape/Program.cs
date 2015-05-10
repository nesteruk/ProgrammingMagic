namespace MagicScrape
{
  using System;
  using System.Collections.Generic;
  using System.IO;
  using System.Text;
  using System.Threading;
  using System.Xml.Linq;
  using WatiN.Core;

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
        if (maxPage == -1)
        {
          throw new Exception("Failed to find paging controls :(");
        }
        var cardIds = new HashSet<string>();

        while (currentPage <= maxPage)
        {
          s = string.Format(startPage, currentPage, cardSet.Replace(" ", "%20"));
          if (currentPage > 1) ie.GoTo(s);

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
          Thread.Sleep(1000);
        }

        var set = new XElement("set", new XAttribute("name", cardSet));

        foreach (var id in cardIds)
          set.Add(ProcessCard(id));

        File.WriteAllText(cardSet + ".xml", set.ToString(), Encoding.ASCII);
      }
    }

    private static XElement ProcessCard(string cardId)
    {
      var url = "http://gatherer.wizards.com/Pages/Card/Details.aspx?printed=false&multiverseid=" + cardId;
      ie.GoTo(url);

      var nameRowDiv = ie.Div(Find.ById(id => id.EndsWith("nameRow")));
      var name = nameRowDiv.Divs[1].Text;
      string manaCost = "";
      var manaContainerDiv = ie.Div(Find.ById(id => id.EndsWith("manaRow")));
      // lands don't have this, so...
      if (manaContainerDiv.Exists && manaContainerDiv.Divs.Count > 1)
      {
        var manaDiv = manaContainerDiv.Divs[1];
        foreach (var img in manaDiv.Images)
        {
          switch (img.Alt)
          {
            case "Red":
              manaCost += "R";
              break;
            case "Blue":
              manaCost += "U";
              break;
            case "White":
              manaCost += "W";
              break;
            case "Green":
              manaCost += "G";
              break;
            case "Black":
              manaCost += "B";
              break;
            default:
              int dummy;
              if (int.TryParse(img.Alt, out dummy))
              {
                manaCost += img.Alt;
                break;
              }
              throw new Exception("Mana cost " + img.Alt + " not supported.");
          }
        }
      }
      var types = ie.Div(Find.ById(id => id.EndsWith("typeRow"))).Divs[1].Text;
      var text = ie.Div(Find.ById(id => id.EndsWith("textRow"))).Divs[1].Text;
      var rarity = ie.Div(Find.ById(id => id.EndsWith("rarityRow"))).Divs[1].Text;
      var number = ie.Div(Find.ById(id => id.EndsWith("numberRow"))).Divs[1].Text;

      var card = new XElement("card", new XAttribute("number", number),
        new XAttribute("name", name), new XAttribute("mana_cost", manaCost),
        new XAttribute("types", types), new XAttribute("text", text),
        new XAttribute("rarity", rarity));
      return card;
    }
  }
}
