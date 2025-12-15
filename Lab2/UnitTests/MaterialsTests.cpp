#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/materials/Material.h"
#include "../Lab2/src/materials/BuildingMaterial.h"
#include "../Lab2/src/materials/FinishingMaterial.h"
#include "../Lab2/src/materials/Tool.h"
#include "../Lab2/src/materials/Warehouse.h"
#include "../Lab2/src/materials/Delivery.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(MaterialsTests)
    {
    public:

        TEST_METHOD(Material_Base_Increase_And_Reserve)
        {
            Material m(1, "Cement", "kg", 100, 5.0, "SupplierA");

            Assert::AreEqual(100, m.getQuantity());
            Assert::AreEqual(5.0, m.getUnitPrice());
            Assert::AreEqual(500.0, m.getTotalCost());

            m.increaseQuantity(50);
            Assert::AreEqual(150, m.getQuantity());

            bool reserved = m.reserve(30);
            Assert::IsTrue(reserved);
            Assert::AreEqual(120, m.getQuantity());

            bool failReserve = m.reserve(200);
            Assert::IsFalse(failReserve);
            Assert::AreEqual(120, m.getQuantity());
        }

        TEST_METHOD(BuildingMaterial_TotalCost_WithDensity)
        {
            BuildingMaterial bm(2, "Brick", "pcs", 1000, 0.5, "SupplierB",
                "B25", true, 900.0);

            double baseCost = bm.Material::getTotalCost();
            double cost = bm.getTotalCost();

            Assert::AreEqual(500.0, baseCost);
            Assert::IsTrue(cost > baseCost);
            Assert::AreEqual(std::string("B25"), bm.getStrengthClass());
            Assert::IsTrue(bm.isForOutdoorUse());
            Assert::AreEqual(900.0, bm.getDensity());
        }

        TEST_METHOD(FinishingMaterial_Coverage)
        {
            FinishingMaterial fm(3, "Paint", "l", 10, 20.0, "SupplierC",
                "white", "matte", 15.0);

            Assert::AreEqual(std::string("white"), fm.getColor());
            Assert::AreEqual(std::string("matte"), fm.getFinishType());
            Assert::AreEqual(15.0, fm.getCoverage());

            double area = fm.getCoverableArea();
            Assert::AreEqual(150.0, area);
        }

        TEST_METHOD(Tool_Checkout_Return_Service)
        {
            Tool t(4, "Drill", "electric", 5, "good", Date(1, 1, 2024));

            bool ok = t.checkout(2);
            Assert::IsTrue(ok);
            Assert::AreEqual(3, t.getQuantity());

            bool fail = t.checkout(10);
            Assert::IsFalse(fail);
            Assert::AreEqual(3, t.getQuantity());

            t.returnBack(1);
            Assert::AreEqual(4, t.getQuantity());

            Date serviceDate(10, 2, 2024);
            t.markServiced(serviceDate);
            Assert::AreEqual(std::string("good"), t.getCondition());
            Assert::AreEqual(serviceDate.getDay(), t.getLastService().getDay());
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Tool t;
            Assert::AreEqual(0, t.getId());
            Assert::AreEqual(std::string(""), t.getName());
            Assert::AreEqual(std::string(""), t.getToolType());
            Assert::AreEqual(0, t.getQuantity());
            Assert::AreEqual(std::string("good"), t.getCondition());

            Warehouse w;
            Assert::AreEqual(0, w.getId());
            Assert::IsNull(w.getAddress());
            Assert::AreEqual(0.0, w.getMaxValue(), 1e-6);
            Assert::AreEqual<size_t>(0, w.getMaterials().size());
            Assert::AreEqual<size_t>(0, w.getTools().size());
        }

        TEST_METHOD(Warehouse_Add_Find_TotalValue)
        {
            Address addr("Warehouse st. 1", "Minsk", "220000", "Belarus");

            Warehouse w(10, &addr, 100000.0);

            Material m1(5, "Cement", "kg", 100, 5.0, "Sup1");
            Material m2(6, "Sand", "kg", 200, 2.0, "Sup2");
            Tool t1(7, "Hammer", "hand", 10, "good", Date(1, 1, 2024));

            w.addMaterial(&m1);
            w.addMaterial(&m2);
            w.addTool(&t1);

            auto* foundMat = w.findMaterialByName("Sand");
            Assert::IsNotNull(foundMat);
            Assert::AreEqual(std::string("Sand"), foundMat->getName());

            auto* foundTool = w.findToolByName("Hammer");
            Assert::IsNotNull(foundTool);

            double value = w.calculateTotalValue();
            Assert::AreEqual(1900.0, value);
        }

        TEST_METHOD(Delivery_Status_And_Materials)
        {
            Address addr1("Warehouse st. 1", "Minsk", "220000", "Belarus");
            Address addr2("Warehouse st. 2", "Minsk", "220001", "Belarus");

            Warehouse from(20, &addr1, 50000.0);
            Warehouse to(21, &addr2, 50000.0);

            Delivery d(1, &from, &to, Date(5, 3, 2025));

            Material m1(8, "Tile", "m2", 50, 10.0, "Sup3");
            Material m2(9, "Glue", "kg", 20, 8.0, "Sup4");

            d.addMaterial(&m1);
            d.addMaterial(&m2);

            Assert::AreEqual(std::string("planned"), d.getStatus());
            Assert::AreEqual<size_t>(2, d.getMaterials().size());

            d.start();
            Assert::AreEqual(std::string("in_progress"), d.getStatus());

            d.complete();
            Assert::AreEqual(std::string("completed"), d.getStatus());
        }

    };
    TEST_CLASS(BuildingMaterialTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            BuildingMaterial m;
            Assert::AreEqual(std::string(""), m.getStrengthClass());
            Assert::IsFalse(m.isForOutdoorUse());
            Assert::AreEqual(0.0, m.getDensity(), 1e-6);
        }

        TEST_METHOD(Setters_UpdateFields)
        {
            BuildingMaterial m;

            m.setStrengthClass("M300");
            m.setForOutdoorUse(true);
            m.setDensity(1200.5);

            Assert::AreEqual(std::string("M300"), m.getStrengthClass());
            Assert::IsTrue(m.isForOutdoorUse());
            Assert::AreEqual(1200.5, m.getDensity(), 1e-6);
        }
    };
}
