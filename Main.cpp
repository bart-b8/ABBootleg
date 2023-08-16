#include "Component.h"
#include "Config.h"
#include "Menu.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>

// #define TEST
#ifdef TEST
#include "./Context.h"
#include "./Entity.h"
#include "./Engine.h"
#include "./Point.h"
#include "./Target_Component.h"

int test_Config_Set() {
  int count = 0;
  std::cout << "Config before Setting config. Should be empty." << endl;
  Config::Get().Print(Config::Get().Map());
  std::cout << endl << endl;
  std::cout << "Initially config map is empty: " << Config::Get().Map().empty()
            << endl;
  if (!Config::Get().Map().empty()) {
    std::cout << "First fault. Expected true got: "
              << Config::Get().Map().empty() << endl;
    count++;
  }
  if (Config::Get().Set("./assets/config/config.ini")) {
    std::cout << "Config file read without issues." << endl;
  } else {
    std::cout << "Config file error!" << std::endl;
    count++;
  }
  std::cout << endl
            << "Testing Parameters: Map should be printed below:" << endl;
  Config::Get().Print(Config::Get().Map());
  std::cout << endl << endl;
  if (Config::Get().Map()["game.fps"] == 60.0) {
    std::cout << "game.fps was read correctly as: "
              << Config::Get().Map()["game.fps"] << endl;
  } else {
    count++;
    std::cout << "game.fps was read incorrectly as: "
              << Config::Get().Map()["game.fps"] << endl;
  }
  std::cout << "Number of tests to fail: " << count << endl << endl;
  if (!count) {
    std::cout << "PASSED config tests" << endl;
  }
  return count;
}

void print_Point(Point p) {
  std::cout << "Point:" << endl
            << "\tx: " << p.x_ << endl
            << "\ty: " << p.y_ << endl;
}
int test_Point() {
  int count = 0;
  std::cout << "Test 1: Create Point object:" << endl;
  Point p1 = Point(0, 0);
  std::cout << "The first Point: " << endl;
  print_Point(p1);
  if (p1.x_ == 0 && p1.y_ == 0) {
    std::cout << "P1 goed gecreert." << endl;
  } else {
    count++;
    std::cout << "P1 niet goed gecreert." << endl << "FAULT!" << endl;
  }

  std::cout << "Point test 2: Lengte" << endl;
  Point p2 = Point(0, 5);
  Point p3 = Point(3, 4);
  Point p4 = Point(-3, 4);
  Point p5 = Point(3, -4);
  Point p6 = Point(-3, -4);
  if (p2.Length() == 5 && p3.Length() == 5 && p4.Length() == 5 &&
      p5.Length() == 5 && p6.Length() == 5) {
    std::cout << "Length is calculated correctly in all quadrants." << endl;
  } else {
    count++;
    std::cout << "FAIL: Length is not calculated correctly." << endl;
  }

  std::cout << "Point test 3: Normalize()" << endl;
  Point p7 = p2;
  p7.Normalize();
  if (p7.x_ == 0 && p7.y_ == 1) {
    std::cout << "Normalize work ok. From p2: " << endl;
    print_Point(p2);
    std::cout << "Normalized: p7: " << endl;
    print_Point(p7);
  } else {
    count++;
    std::cout << "FAIL: Normalize() gave unexpected result." << endl;
  }

  std::cout << "Point test 4: operator >>: " << endl;
  Point p8 = Point(-2, 2);
  Point p9 = Point(1, 1);
  if (p8 >> p9 == 0) {
    std::cout << "Inwendig product met >> goed berekend." << endl;
  } else {
    count++;
    std::cout << "FAIL: Inwendig product niet correct berekend" << endl;
  }

  std::cout << "Point test 5: operator - : " << endl;
  if ((p4 - p5).x_ == -6 && (p4 - p5).y_ == 8) {
    std::cout << "Verschil is correct berekend" << endl;
  } else {
    count++;
    std::cout << "FAIL: Verschil is niet correct berekend." << endl;
  }

  std::cout << "Total result for Point tests: " << count << " Fails" << endl;
  if (!count) {
    std::cout << "POINT Tests SUCCES" << endl;
  } else {
    std::cout << "POINT Test FAILURE" << endl;
  }
  return count;
}

int test_Context() {
  int count = 0;
  Context _ct;
  _ct.pth_level = "./assets/levels/level1.txt";
  std::cout << "TEST: Context," << endl;
  std::cout << "After constructing context and assigning pth level: " << endl;
  std::cout << "The path to the level file: " << _ct.pth_level << endl;
  if (_ct.pth_level.filename() != "level1.txt") {
    count++;
    std::cout << "FAIL: Path level has not been recoverd correctly.";
  }
  std::cout << "Total result for Context tests: " << count << " Fails" << endl;
  if (!count) {
    std::cout << "Context Tests SUCCES" << endl;
  } else {
    std::cout << "Context Test FAILURE" << endl;
  }
  return count;
}

int test_Entity() {
  int count = 0;
  Entity tstEntity;

  std::cout << "Entity net aangemaakt. " << endl;

  std::cout << "Test if all functions work for 1 component" << endl;
  Target_Component *trgtComp = new Target_Component;
  tstEntity.Add(trgtComp);
  std::vector<Component *> vec_comp = tstEntity.GetComponents();
  if (vec_comp[0] == trgtComp) {
    std::cout << "We find the correct address" << endl;
  } else {
    count++;
    std::cout << "FAIL: in recovering ptr to component.";
  }
  std::vector<Component::Tag> vec_tags = tstEntity.GetTags();
  if (vec_tags[0] == Component::Target) {
    std::cout << "Tags correctly found via GetTags()." << endl;
  } else {
    count++;
    std::cout << "FAIL: Tags not correctly found using gettags() " << endl;
  }
  Component *res = tstEntity.GetComponent(Component::Target);
  if (res == trgtComp) {
    std::cout << "We get correct adress searching with tags. " << endl;
  } else {
    count++;
    std::cout << "FAIL: Component not found using Tags" << endl;
  }

  std::cout << "Test for 2 components" << endl;
  std::cout << "No tests implemented yet." << endl;

  // delete trgtComp;
  std::cout << "Total result for Entity tests: " << count << " Fails" << endl;
  if (!count) {
    std::cout << "Entity Tests SUCCES" << endl;
  } else {
    std::cout << "Entity Test FAILURE" << endl;
  }
  return count;
}

int test_EntityStream() {
  int count = 0;
  EntityStream strm;
  Target_Component * tgtcomp = new Target_Component;
  Entity enty;
  enty.Add(tgtcomp);
  strm.EntityUpdated(&enty, enty.GetTags(), false);
  std::set<Entity *> wthTagTarget = strm.WithTag(Component::Target);
  std::set<Entity *> wthTagSprite = strm.WithTag(Component::Sprite);
  if (wthTagTarget.count(&enty) == 1) { std::cout << "Entity with Target tag found well." << endl; }
  else {
    count++;
    std::cout << "FAIL: Entity with Target tag not found well." << endl; 
  }
  if (wthTagSprite.empty()) { std::cout << "No Entities with sprite components. As expected." << endl; }
  else {
    count++;
    std::cout << "FAIL: There where no enitites expected with sprite component." << endl;
  }

  strm.EntityUpdated(&enty, enty.GetTags(), true);
  wthTagTarget = strm.WithTag(Component::Target);
  if (wthTagTarget.empty()) { std::cout << "No Entities with target components. As expected." << endl; }
  else {
    count++;
    std::cout << "FAIL: There where no enitites expected with Target component." << endl;
  }

  std::cout << "Total result for EntityStream tests: " << count << " Fails" << endl;
  if (!count) {
    std::cout << "EntityStream Tests SUCCES" << endl;
  } else {
    std::cout << "EntityStream Test FAILURE" << endl;
  }
  return count;
}

int test_Engine() {
  int count = 0;

  Target_Component * tgtcomp = new Target_Component;
  Entity * entity1 = new Entity;
  entity1->Add(tgtcomp);
  Context context = Context();
  Engine engine = Engine(context);

  std::cout << "TESTs for Engine" << endl;
  std::cout << "Test 1: AddEntity" << endl;
  // Should add entity to engine via pointer
  // AND should update the entity stream.
  engine.AddEntity(entity1);
  std::vector<Entity*> entities = engine.GetEntities();
  if (entities[0] == entity1) {
    std::cout << "entitity1 found in Engine" << endl;
  } else {
    count++;
    std::cout << "FAIL: Entity1 not found." << endl;
  }
  EntityStream strm = engine.GetEntityStream();
  std::set<Entity*> withTagTarget = strm.WithTag(Component::Target);
  std::set<Entity*> withTagSprite = strm.WithTag(Component::Sprite);
  if (withTagTarget.count(entity1) == 1) { std::cout << "Entity with Target tag found well." << endl; }
  else {
    count++;
    std::cout << "FAIL: Entity with Target tag not found well." << endl; 
  }
  if (withTagSprite.empty()) { std::cout << "No Entities with sprite components. As expected." << endl; }
  else {
    count++;
    std::cout << "FAIL: There where no enitites expected with sprite component." << endl;
  }

  engine.RemoveEntity(entity1);
  strm = engine.GetEntityStream();
  withTagTarget = strm.WithTag(Component::Target);
  if (withTagTarget.empty()) { std::cout << "No Entities with target components. As expected." << endl; }
  else {
    count++;
    std::cout << "FAIL: There where no enitites expected with Target component." << endl;
  }

  delete entity1;
  std::cout << "Total result for Engine tests: " << count << " Fails" << endl;
  if (!count) {
    std::cout << "Engine Tests SUCCES" << endl;
  } else {
    std::cout << "Engine Test FAILURE" << endl;
  }
  return count;
}
#endif  // TEST

void InitWsl() {
  std::ifstream inFile;
  inFile.open("/proc/version");
  if (!inFile) {
    std::cerr << "ERROR: unable to open /proc/version";
    exit(1);
  }
  std::string line;
  bool running_on_wsl = false;
  while (std::getline(inFile, line)) {
    if (line.find("Microsoft") != std::string::npos) {
      std::cout << "INFO: Detected WSL." << std::endl;
      std::cout << line << std::endl;
      running_on_wsl = true;
    }
  }
  if (running_on_wsl) {
    std::cout << "INFO: Initialising WSL Audio and Video." << std::endl;
    char display_key[] = "DISPLAY";
    char display_value[] = ":0";
    setenv(display_key, display_value, 1);

    char audio_key[] = "PULSE_SERVER";
    char audio_value[] = "tcp:127.0.0.1";
    setenv(audio_key, audio_value, 1);

    if (system("nc -vzw3 127.0.0.1 4713") != 0) {
      std::cout << "\e[31mERROR: PulseAudio is niet gevonden! Start eerst "
                   "PulseAudio vóór je het project uitvoert!\e[0m"
                << std::endl;
      std::cout << "\e[31mIndien je dit al gedaan hebt; herstart je computer, "
                   "start PulseAudio opnieuw en probeer nogmaals.\e[0m"
                << std::endl;
      exit(1);
    }
    if (system(" nc -vzw3 127.0.0.1 6000") != 0) {
      std::cout << "\e[31mERROR: De X server is niet gevonden! Start eerst de "
                   "X Server door middel van 'XLaunch' vóór je het project "
                   "uitvoert!\e[0m"
                << std::endl;
      exit(1);
    }
  } else {
    std::cout << "INFO: Not running on WSL. Windows initialisation skipped."
              << std::endl;
  }
}

int main(int argc, char **argv) {
  InitWsl();

#ifdef TEST
  int count = 0;
  count += test_Config_Set();
  std::cout << endl << endl;
  count += test_Point();
  std::cout << endl << endl;
  count += test_Context();
  std::cout << endl << endl;
  count += test_Entity();
  std::cout << endl << endl;
  count += test_EntityStream();
  std::cout << endl << endl;
  count += test_Engine();
  std::cout << endl << endl;

  std::cout << "Total FAILED: " << count << endl;
  if (!count) {
    std::cout << "TESTS SUCCES";
  } else {
    std::cout << "TESTS FAILED";
  }
  return count;
#endif // TEST

  if (!Config::Get().Set("./assets/config/config.ini")) {
    std::cout << "Config file error!" << std::endl;
    return -1;
  }

  Allkit::Get().Init();

  Menu menu;
  menu.Run();

  Allkit::Get().Destroy();

  return 0;
}
