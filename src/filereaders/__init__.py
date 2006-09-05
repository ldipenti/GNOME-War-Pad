# filereaders module initialization

from casefile import CaseInsensitiveFile
from pdata import PDataFile
from racenm import RaceNMFile
from xyplan import XYPlanFile
from bdata import BDataFile
from shipxy import ShipXYFile
from ship import ShipFile
from target import TargetFile
from kore import KoreFile
from planetnm import PlanetNMFile
from beamspec import BeamspecFile
from engspec import EngspecFile

__all__ = ["PDataFile", "RaceNMFile", "XYPlanFile", "BDataFile", "ShipXYFile", "ShipFile", "TargetFile", "KoreFile", "CaseInsensitiveFile", "PlanetNMFile", "BeamspecFile", "EngspecFile"]
